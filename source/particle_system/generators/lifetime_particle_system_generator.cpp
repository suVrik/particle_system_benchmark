#include "particle_system/generators/lifetime_particle_system_generator.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_primitive.h"
#include "particle_system/particle_system_stream.h"

LifetimeParticleSystemGenerator::LifetimeParticleSystemGenerator(float min_lifetime, float max_lifetime)
    : m_lifetime_range(max_lifetime - min_lifetime)
    , m_lifetime_offset(min_lifetime)
{
}

void LifetimeParticleSystemGenerator::generate(ParticleSystemData& data, ParticleSystemPrimitive& primitive, size_t begin_index, size_t end_index) const {
    Random& random = data.get_random();

    float* current_lifetime_stream_data = data.get_stream_data<float>(ParticleSystemStream::CURRENT_LIFETIME);
    float* total_lifetime_stream_data = data.get_stream_data<float>(ParticleSystemStream::TOTAL_LIFETIME);

    if (total_lifetime_stream_data == nullptr) {
        for (size_t i = begin_index; i < end_index; i++) {
            current_lifetime_stream_data[i] = random.rand_float() * m_lifetime_range + m_lifetime_offset;
        }
    } else {
        for (size_t i = begin_index; i < end_index; i++) {
            total_lifetime_stream_data[i] = current_lifetime_stream_data[i] = random.rand_float() * m_lifetime_range + m_lifetime_offset;
        }
    }
}

ParticleSystemStreamMask LifetimeParticleSystemGenerator::get_stream_mask() const {
    // Also accesses `TOTAL_LIFETIME`, but only if requested by anyone else.
    return ParticleSystemStreamMask::CURRENT_LIFETIME;
}
