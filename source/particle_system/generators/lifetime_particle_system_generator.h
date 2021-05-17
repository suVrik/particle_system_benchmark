#pragma once

#include "particle_system/generators/particle_system_generator.h"

struct LifetimeParticleSystemGenerator : public ParticleSystemGenerator {
public:
    LifetimeParticleSystemGenerator(float min_lifetime, float max_lifetime);

    void generate(ParticleSystemData& data, ParticleSystemPrimitive& primitive, size_t begin_index, size_t end_index) const override;

    ParticleSystemStreamMask get_stream_mask() const override;

private:
    float m_lifetime_range;
    float m_lifetime_offset;
};
