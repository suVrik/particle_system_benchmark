#include "particle_system/updaters/velocity_over_lifetime_particle_system_updater.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_stream.h"

#ifdef USE_SSE2
#include <emmintrin.h>
#include <immintrin.h>
#endif // USE_SSE2

VelocityOverLifetimeParticleSystemUpdater::VelocityOverLifetimeParticleSystemUpdater(const float3& from_velocity, const float3& to_velocity)
#ifdef VELOCITY_LAYOUT_XYZW
    : m_velocity_range(from_velocity - to_velocity, 0.f)
    , m_velocity_offset(from_velocity, 0.f)
#else
#ifdef USE_SSE2
    : m_velocity_range{ float4(from_velocity.x - to_velocity.x), float4(from_velocity.y - to_velocity.y), float4(from_velocity.z - to_velocity.z) }
    , m_velocity_offset{ float4(from_velocity.x), float4(from_velocity.y), float4(from_velocity.z) }
#else
    : m_velocity_range(from_velocity - to_velocity)
    , m_velocity_offset(from_velocity)
#endif // USE_SSE2
#endif // VELOCITY_LAYOUT_XYZW
{
}

void VelocityOverLifetimeParticleSystemUpdater::update(ParticleSystemData& data, float elapsed_time) const {
    float* total_lifetime_stream_data   = data.get_stream_data<float>(ParticleSystemStream::TOTAL_LIFETIME);
    float* current_lifetime_stream_data = data.get_stream_data<float>(ParticleSystemStream::CURRENT_LIFETIME);

#ifdef VELOCITY_LAYOUT_XYZW
    float4* velocity_xyzw_stream_data = data.get_stream_data<float4>(ParticleSystemStream::VELOCITY_XYZW);

#ifdef USE_SSE2
    __m128 xyzw_range_xmm  = _mm_load_ps(&m_velocity_range);
    __m128 xyzw_offset_xmm = _mm_load_ps(&m_velocity_offset);
    
    for (size_t i = 0; i < data.get_size(); i++) {
        __m128 relative_lifetime = _mm_set1_ps(current_lifetime_stream_data[i] / total_lifetime_stream_data[i]);

        _mm_store_ps(&velocity_xyzw_stream_data[i], _mm_fmadd_ps(relative_lifetime, xyzw_range_xmm, xyzw_offset_xmm));
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        velocity_xyzw_stream_data[i] = current_lifetime_stream_data[i] / total_lifetime_stream_data[i] * m_velocity_range + m_velocity_offset;
    }
#endif // USE_SSE2
#else
    float* velocity_x_stream_data = data.get_stream_data<float>(ParticleSystemStream::VELOCITY_X);
    float* velocity_y_stream_data = data.get_stream_data<float>(ParticleSystemStream::VELOCITY_Y);
    float* velocity_z_stream_data = data.get_stream_data<float>(ParticleSystemStream::VELOCITY_Z);

#ifdef USE_SSE2
    __m128 x_range_xmm = _mm_load_ps(&m_velocity_range[0]);
    __m128 y_range_xmm = _mm_load_ps(&m_velocity_range[1]);
    __m128 z_range_xmm = _mm_load_ps(&m_velocity_range[2]);

    __m128 x_offset_xmm = _mm_load_ps(&m_velocity_offset[0]);
    __m128 y_offset_xmm = _mm_load_ps(&m_velocity_offset[1]);
    __m128 z_offset_xmm = _mm_load_ps(&m_velocity_offset[2]);

    for (size_t i = 0; i < data.get_size(); i += 4) {
        __m128 current_lifetime_xmm  = _mm_load_ps(current_lifetime_stream_data + i);
        __m128 total_lifetime_xmm    = _mm_load_ps(total_lifetime_stream_data + i);
        __m128 relative_lifetime_xmm = _mm_div_ps(current_lifetime_xmm, total_lifetime_xmm);

        __m128 x_xmm = _mm_fmadd_ps(relative_lifetime_xmm, x_range_xmm, x_offset_xmm);
        __m128 y_xmm = _mm_fmadd_ps(relative_lifetime_xmm, y_range_xmm, y_offset_xmm);
        __m128 z_xmm = _mm_fmadd_ps(relative_lifetime_xmm, z_range_xmm, z_offset_xmm);

        _mm_store_ps(velocity_x_stream_data + i, x_xmm);
        _mm_store_ps(velocity_y_stream_data + i, y_xmm);
        _mm_store_ps(velocity_z_stream_data + i, z_xmm);
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        float relative_lifetime = current_lifetime_stream_data[i] / total_lifetime_stream_data[i];

        velocity_x_stream_data[i] = relative_lifetime * m_velocity_range.x + m_velocity_offset.x;
        velocity_y_stream_data[i] = relative_lifetime * m_velocity_range.y + m_velocity_offset.y;
        velocity_z_stream_data[i] = relative_lifetime * m_velocity_range.z + m_velocity_offset.z;
    }
#endif // USE_SSE2
#endif // VELOCITY_LAYOUT_XYZW
}

ParticleSystemStreamMask VelocityOverLifetimeParticleSystemUpdater::get_stream_mask() const {
#ifdef VELOCITY_LAYOUT_XYZW
    return ParticleSystemStreamMask::TOTAL_LIFETIME |
           ParticleSystemStreamMask::CURRENT_LIFETIME |
           ParticleSystemStreamMask::VELOCITY_XYZW;
#else
    return ParticleSystemStreamMask::TOTAL_LIFETIME |
           ParticleSystemStreamMask::CURRENT_LIFETIME |
           ParticleSystemStreamMask::VELOCITY_X |
           ParticleSystemStreamMask::VELOCITY_Y |
           ParticleSystemStreamMask::VELOCITY_Z;
#endif // VELOCITY_LAYOUT_XYZW
}
