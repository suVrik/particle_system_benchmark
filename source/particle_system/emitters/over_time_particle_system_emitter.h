#pragma once

#include "particle_system/emitters/particle_system_emitter.h"

class OverTimeParticleSystemEmitter : public ParticleSystemEmitter {
public:
    OverTimeParticleSystemEmitter(float emit_per_second_from, float emit_per_second_to);

    size_t emit(ParticleSystemData& data, ParticleSystemPrimitive& primitive, float elapsed_time) const override;

private:
    float m_emit_per_second_half_range;
    float m_emit_per_second_offset;
};
