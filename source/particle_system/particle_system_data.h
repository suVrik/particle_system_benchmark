#pragma once

#include "particle_system/auxiliary/random.h"
#include "particle_system/particle_system_stream.h"

#include <memory>
#include <vector>

class ParticleSystemDescriptor;
class ParticleSystemPrimitive;

class ParticleSystemData {
public:
#ifdef CONTIGUOUS_PRIMITIVE_DATA
    ParticleSystemData(ParticleSystemDescriptor& descsriptor, std::vector<std::unique_ptr<ParticleSystemPrimitive>>&& primitives);
#else
    ParticleSystemData(ParticleSystemDescriptor& descsriptor, std::unique_ptr<ParticleSystemPrimitive>&& primitive);
#endif // CONTIGUOUS_PRIMITIVE_DATA

    ParticleSystemData(ParticleSystemData&& another);
    ~ParticleSystemData();

    void update(float elapsed_time);
    void reserve(size_t capacity);

    template <typename T>
    T* get_stream_data(ParticleSystemStream stream) {
        return reinterpret_cast<T*>(m_streams[static_cast<size_t>(stream)]);
    }

    Random& get_random() {
        return m_random;
    }

    size_t get_size() const {
        return m_size;
    }

    float get_time() const;

private:
    ParticleSystemDescriptor& m_descsriptor;

#ifdef CONTIGUOUS_PRIMITIVE_DATA
    std::vector<std::unique_ptr<ParticleSystemPrimitive>> m_primitives;
#else
    std::unique_ptr<ParticleSystemPrimitive> m_primitive;
#endif // CONTIGUOUS_PRIMITIVE_DATA

    uint8_t* m_streams[PARTICLE_SYSTEM_STREAM_COUNT];
    size_t m_size;
    size_t m_capacity;

    Random m_random;
};
