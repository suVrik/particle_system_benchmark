#pragma once

#include "particle_system/auxiliary/math.h"

class ParticleSystemPrimitive {
public:
    ParticleSystemPrimitive(const float4x4& global_transform)
        : m_global_transform(global_transform)
        , m_time(0.f)
    {
    }

    const float4x4& get_global_transform() const {
        return m_global_transform;
    }

    void set_global_transform(const float4x4& transform) {
        m_global_transform = transform;
    }

    float get_time() const {
        return m_time;
    }

    void set_time(float time) {
        m_time = time;
    }

private:
    alignas(16) float4x4 m_global_transform;
    float m_time;
};
