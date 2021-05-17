#include "particle_system/updaters/color_over_lifetime_particle_system_updater.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_stream.h"

#ifdef USE_SSE2
#include <emmintrin.h>
#include <immintrin.h>
#endif // USE_SSE2

ColorOverLifetimeParticleSystemUpdater::ColorOverLifetimeParticleSystemUpdater(const float4& from_color, const float4& to_color)
#ifdef COLOR_LAYOUT_RGBA
    : m_color_range(from_color - to_color)
    , m_color_offset(from_color)
#else
#ifdef USE_SSE2
    : m_color_range{ float4(from_color.r - to_color.r), float4(from_color.g - to_color.g), float4(from_color.b - to_color.b), float4(from_color.a - to_color.a) }
    , m_color_offset{ float4(from_color.r), float4(from_color.g), float4(from_color.b), float4(from_color.a) }
#else
    : m_color_range(from_color - to_color)
    , m_color_offset(from_color)
#endif // USE_SSE2
#endif // COLOR_LAYOUT_RGBA
{
}

void ColorOverLifetimeParticleSystemUpdater::update(ParticleSystemData& data, float elapsed_time) const {
    float* total_lifetime_stream_data = data.get_stream_data<float>(ParticleSystemStream::TOTAL_LIFETIME);
    float* current_lifetime_stream_data = data.get_stream_data<float>(ParticleSystemStream::CURRENT_LIFETIME);

#ifdef COLOR_LAYOUT_RGBA
    float4* color_rgba_stream_data = data.get_stream_data<float4>(ParticleSystemStream::COLOR_RGBA);
    
#ifdef USE_SSE2
    __m128 rgba_range_xmm  = _mm_load_ps(&m_color_range);
    __m128 rgba_offset_xmm = _mm_load_ps(&m_color_offset);

    for (size_t i = 0; i < data.get_size(); i++) {
        __m128 relative_lifetime = _mm_set1_ps(current_lifetime_stream_data[i] / total_lifetime_stream_data[i]);

        _mm_store_ps(&color_rgba_stream_data[i], _mm_fmadd_ps(relative_lifetime, rgba_range_xmm, rgba_offset_xmm));
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        color_rgba_stream_data[i] = current_lifetime_stream_data[i] / total_lifetime_stream_data[i] * m_color_range + m_color_offset;
    }
#endif // USE_SSE2
#else
    float* color_r_stream_data = data.get_stream_data<float>(ParticleSystemStream::COLOR_R);
    float* color_g_stream_data = data.get_stream_data<float>(ParticleSystemStream::COLOR_G);
    float* color_b_stream_data = data.get_stream_data<float>(ParticleSystemStream::COLOR_B);
    float* color_a_stream_data = data.get_stream_data<float>(ParticleSystemStream::COLOR_A);

#ifdef USE_SSE2
    __m128 r_range_xmm = _mm_load_ps(&m_color_range[0]);
    __m128 g_range_xmm = _mm_load_ps(&m_color_range[1]);
    __m128 b_range_xmm = _mm_load_ps(&m_color_range[2]);
    __m128 a_range_xmm = _mm_load_ps(&m_color_range[3]);

    __m128 r_offset_xmm = _mm_load_ps(&m_color_offset[0]);
    __m128 g_offset_xmm = _mm_load_ps(&m_color_offset[1]);
    __m128 b_offset_xmm = _mm_load_ps(&m_color_offset[2]);
    __m128 a_offset_xmm = _mm_load_ps(&m_color_offset[3]);

    for (size_t i = 0; i < data.get_size(); i += 4) {
        __m128 current_lifetime_xmm  = _mm_load_ps(current_lifetime_stream_data + i);
        __m128 total_lifetime_xmm    = _mm_load_ps(total_lifetime_stream_data + i);
        __m128 relative_lifetime_xmm = _mm_div_ps(current_lifetime_xmm, total_lifetime_xmm);

        __m128 r_xmm = _mm_fmadd_ps(relative_lifetime_xmm, r_range_xmm, r_offset_xmm);
        __m128 g_xmm = _mm_fmadd_ps(relative_lifetime_xmm, g_range_xmm, g_offset_xmm);
        __m128 b_xmm = _mm_fmadd_ps(relative_lifetime_xmm, b_range_xmm, b_offset_xmm);
        __m128 a_xmm = _mm_fmadd_ps(relative_lifetime_xmm, a_range_xmm, a_offset_xmm);

        _mm_store_ps(color_r_stream_data + i, r_xmm);
        _mm_store_ps(color_g_stream_data + i, g_xmm);
        _mm_store_ps(color_b_stream_data + i, b_xmm);
        _mm_store_ps(color_a_stream_data + i, a_xmm);
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        float relative_lifetime = current_lifetime_stream_data[i] / total_lifetime_stream_data[i];

        color_r_stream_data[i] = relative_lifetime * m_color_range.r + m_color_offset.r;
        color_g_stream_data[i] = relative_lifetime * m_color_range.g + m_color_offset.g;
        color_b_stream_data[i] = relative_lifetime * m_color_range.b + m_color_offset.b;
        color_a_stream_data[i] = relative_lifetime * m_color_range.a + m_color_offset.a;
    }
#endif // USE_SSE2
#endif // COLOR_LAYOUT_RGBA
}

ParticleSystemStreamMask ColorOverLifetimeParticleSystemUpdater::get_stream_mask() const {
#ifdef COLOR_LAYOUT_RGBA
    return ParticleSystemStreamMask::TOTAL_LIFETIME |
           ParticleSystemStreamMask::CURRENT_LIFETIME |
           ParticleSystemStreamMask::COLOR_RGBA;
#else
    return ParticleSystemStreamMask::TOTAL_LIFETIME |
           ParticleSystemStreamMask::CURRENT_LIFETIME |
           ParticleSystemStreamMask::COLOR_R |
           ParticleSystemStreamMask::COLOR_G |
           ParticleSystemStreamMask::COLOR_B |
           ParticleSystemStreamMask::COLOR_A;
#endif // COLOR_LAYOUT_RGBA
}
