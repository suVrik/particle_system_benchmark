#pragma once

#include "particle_system/auxiliary/math.h"
#include "particle_system/updaters/particle_system_updater.h"

class ColorOverLifetimeParticleSystemUpdater : public ParticleSystemUpdater {
public:
    ColorOverLifetimeParticleSystemUpdater(const float4& from_color, const float4& to_color);

    void update(ParticleSystemData& data, float elapsed_time) const override;

    ParticleSystemStreamMask get_stream_mask() const override;

private:
#ifdef COLOR_LAYOUT_RGBA
    alignas(16) float4 m_color_range;
    alignas(16) float4 m_color_offset;
#else
#ifdef USE_SSE2
    alignas(16) float4 m_color_range[4];
    alignas(16) float4 m_color_offset[4];
#else
    float4 m_color_range;
    float4 m_color_offset;
#endif // USE_SSE2
#endif // COLOR_LAYOUT_RGBA
};
