#pragma once

#include "particle_system/auxiliary/math.h"
#include "particle_system/updaters/particle_system_updater.h"

class VelocityOverLifetimeParticleSystemUpdater : public ParticleSystemUpdater {
public:
    VelocityOverLifetimeParticleSystemUpdater(const float3& from_velocity, const float3& to_velocity);

    void update(ParticleSystemData& data, float elapsed_time) const override;

    ParticleSystemStreamMask get_stream_mask() const override;

private:
#ifdef VELOCITY_LAYOUT_XYZW
    alignas(16) float4 m_velocity_range;
    alignas(16) float4 m_velocity_offset;
#else
#ifdef USE_SSE2
    alignas(16) float4 m_velocity_range[3];
    alignas(16) float4 m_velocity_offset[3];
#else
    float3 m_velocity_range;
    float3 m_velocity_offset;
#endif // USE_SSE2
#endif // VELOCITY_LAYOUT_XYZW
};
