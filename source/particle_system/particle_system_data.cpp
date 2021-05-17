#include "particle_system/particle_system_data.h"
#include "particle_system/auxiliary/cpu_profiler.h"
#include "particle_system/auxiliary/math.h"
#include "particle_system/emitters/particle_system_emitter.h"
#include "particle_system/generators/particle_system_generator.h"
#include "particle_system/particle_system_descriptor.h"
#include "particle_system/particle_system_primitive.h"
#include "particle_system/updaters/particle_system_updater.h"

#include <exception>

static const size_t PARTICLE_SYSTEM_STREAM_SIZE[] = {
#ifdef POSITION_LAYOUT_XYZW
    sizeof(float4), // POSITION_XYZW
#else
    sizeof(float),  // POSITION_X
    sizeof(float),  // POSITION_Y
    sizeof(float),  // POSITION_Z
#endif // POSITION_LAYOUT_XYZW

#ifdef VELOCITY_LAYOUT_XYZW
    sizeof(float4), // VELOCITY_XYZW
#else
    sizeof(float),  // VELOCITY_X
    sizeof(float),  // VELOCITY_Y
    sizeof(float),  // VELOCITY_Z
#endif // VELOCITY_LAYOUT_XYZW

#ifdef COLOR_LAYOUT_RGBA
    sizeof(float4), // COLOR_RGBA
#else
    sizeof(float),  // COLOR_R
    sizeof(float),  // COLOR_G
    sizeof(float),  // COLOR_B
    sizeof(float),  // COLOR_A
#endif // COLOR_LAYOUT_RGBA

    sizeof(float),  // TOTAL_LIFETIME
    sizeof(float),  // CURRENT_LIFETIME
};

#ifdef CONTIGUOUS_PRIMITIVE_DATA
ParticleSystemData::ParticleSystemData(ParticleSystemDescriptor& descsriptor, std::vector<std::unique_ptr<ParticleSystemPrimitive>>&& primitives)
    : m_descsriptor(descsriptor)
    , m_primitives(std::move(primitives))
    , m_streams{}
    , m_size(0)
    , m_capacity(0)
    , m_random(1)
{
}

ParticleSystemData::ParticleSystemData(ParticleSystemData&& another)
    : m_descsriptor(another.m_descsriptor)
    , m_primitives(std::move(another.m_primitives))
    , m_size(another.m_size)
    , m_capacity(another.m_capacity)
    , m_random(another.m_random.seed)
{
    std::copy(std::begin(another.m_streams), std::end(another.m_streams), std::begin(m_streams));
    std::fill(std::begin(another.m_streams), std::end(another.m_streams), nullptr);
    another.m_size = another.m_capacity = 0;
}
#else
ParticleSystemData::ParticleSystemData(ParticleSystemDescriptor& descsriptor, std::unique_ptr<ParticleSystemPrimitive>&& primitive)
    : m_descsriptor(descsriptor)
    , m_primitive(std::move(primitive))
    , m_streams{}
    , m_size(0)
    , m_capacity(0)
    , m_random(1)
{
}

ParticleSystemData::ParticleSystemData(ParticleSystemData&& another)
    : m_descsriptor(another.m_descsriptor)
    , m_primitive(std::move(another.m_primitive))
    , m_size(another.m_size)
    , m_capacity(another.m_capacity)
    , m_random(another.m_random.seed)
{
    std::copy(std::begin(another.m_streams), std::end(another.m_streams), std::begin(m_streams));
    std::fill(std::begin(another.m_streams), std::end(another.m_streams), nullptr);
    another.m_size = another.m_capacity = 0;
}
#endif // CONTIGUOUS_PRIMITIVE_DATA

ParticleSystemData::~ParticleSystemData() {
    for (size_t j = 0; j < PARTICLE_SYSTEM_STREAM_COUNT; j++) {
        _aligned_free(m_streams[j]);
    }
}

void ParticleSystemData::update(float elapsed_time) {
    {
        CPU_PROFILER_SCOPE("kill");

        float* current_lifetime_stream_data = get_stream_data<float>(ParticleSystemStream::CURRENT_LIFETIME);
        for (size_t i = 0; i < m_size; ) {
            if (current_lifetime_stream_data[i] <= 0.f) {
                m_size--;

                for (size_t j = 0; j < PARTICLE_SYSTEM_STREAM_COUNT; j++) {
                    if (m_streams[j] != nullptr) {
                        size_t size = PARTICLE_SYSTEM_STREAM_SIZE[j];
                        std::memcpy(m_streams[j] + m_size * size, m_streams[j] + i * size, size);
                    }
                }
            } else {
                i++;
            }
        }
    }

    {
        CPU_PROFILER_SCOPE("emit");

#ifdef CONTIGUOUS_PRIMITIVE_DATA
        for (std::unique_ptr<ParticleSystemPrimitive>& m_primitive : m_primitives)
#endif // CONTIGUOUS_PRIMITIVE_DATA
        {
            size_t begin_index = m_size;
            size_t end_index = begin_index;

            m_primitive->set_time(m_primitive->get_time() + elapsed_time);

            for (const std::unique_ptr<ParticleSystemEmitter>& emitter : m_descsriptor.get_emitters()) {
                end_index += emitter->emit(*this, *m_primitive, elapsed_time);
            }

            if (begin_index != end_index) {
                // We're not measuring memory allocation in this benchmark.
                //reserve(end_index);

                // Just make sure we're not out of bounds.
                if (end_index > m_capacity) {
                    throw std::runtime_error("Out of bounds. Reserve more.");
                }

                m_size = end_index;

                for (const std::unique_ptr<ParticleSystemGenerator>& generator : m_descsriptor.get_generators()) {
                    generator->generate(*this, *m_primitive, begin_index, end_index);
                }
            }
        }
    }

    {
        CPU_PROFILER_SCOPE("update");

        for (const std::unique_ptr<ParticleSystemUpdater>& updater : m_descsriptor.get_updaters()) {
            updater->update(*this, elapsed_time);
        }
    }
}

void ParticleSystemData::reserve(size_t capacity) {
    if (capacity > m_capacity) {
        m_capacity = std::max(m_capacity * 2, capacity);
        for (size_t j = 0; j < PARTICLE_SYSTEM_STREAM_COUNT; j++) {
            if ((m_descsriptor.get_mask() & static_cast<ParticleSystemStreamMask>(1 << j)) != ParticleSystemStreamMask::NONE) {
                size_t size = (m_capacity * PARTICLE_SYSTEM_STREAM_SIZE[j] + 15) & ~15;
                m_streams[j] = reinterpret_cast<uint8_t*>(_aligned_realloc(m_streams[j], size, 16));
            }
        }
    }
}

float ParticleSystemData::get_time() const {
    return m_descsriptor.get_time();
}
