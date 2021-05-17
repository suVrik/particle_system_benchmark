#pragma once

#include "particle_system/auxiliary/math.h"
#include "particle_system/generators/particle_system_generator.h"

class BoxPositionParticleSystemGenerator : public ParticleSystemGenerator {
public:
    BoxPositionParticleSystemGenerator(const float3& inner_size, const float3& outer_size);

    void generate(ParticleSystemData& data, ParticleSystemPrimitive& primitive, size_t begin_index, size_t end_index) const override;

    ParticleSystemStreamMask get_stream_mask() const override;

private:
#ifdef USE_SSE2
    alignas(16) float4 m_size_range;
    alignas(16) float4 m_size_offset;
#else
    float3 m_size_range;
    float3 m_size_offset;
#endif // USE_SSE2
};
