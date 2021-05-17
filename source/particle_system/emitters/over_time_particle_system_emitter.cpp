#include "particle_system/emitters/over_time_particle_system_emitter.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_primitive.h"

OverTimeParticleSystemEmitter::OverTimeParticleSystemEmitter(float emit_per_second_from, float emit_per_second_to)
    : m_emit_per_second_half_range((emit_per_second_to - emit_per_second_from) / 2.f)
    , m_emit_per_second_offset(emit_per_second_from)
{
}

size_t OverTimeParticleSystemEmitter::emit(ParticleSystemData& data, ParticleSystemPrimitive& primitive, float elapsed_time) const {
    float data_time = data.get_time();

    float current_time  = std::min(primitive.get_time(), data_time);
    float previous_time = std::max(current_time - elapsed_time, 0.f);

    float current_factor  = current_time / data_time;
    float previous_factor = previous_time / data_time;

    float current_emitted  = (current_factor * m_emit_per_second_half_range + m_emit_per_second_offset) * current_time;
    float previous_emitted = (previous_factor * m_emit_per_second_half_range + m_emit_per_second_offset) * previous_time;

    return static_cast<size_t>(current_emitted) - static_cast<size_t>(previous_emitted);
}
