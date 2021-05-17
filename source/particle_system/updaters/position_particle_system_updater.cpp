#include "particle_system/updaters/position_particle_system_updater.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_stream.h"

#ifdef USE_SSE2
#include <emmintrin.h>
#endif //USE_SSE2

void PositionParticleSystemUpdater::update(ParticleSystemData& data, float elapsed_time) const {
#if defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW)
    float4* position_xyzw_stream_data = data.get_stream_data<float4>(ParticleSystemStream::POSITION_XYZW);
    float4* velocity_xyzw_stream_data = data.get_stream_data<float4>(ParticleSystemStream::VELOCITY_XYZW);

#ifdef USE_SSE2
    for (size_t i = 0; i < data.get_size(); i++) {
        __m128 position_xmm = _mm_load_ps(&position_xyzw_stream_data[i]);
        __m128 velocity_xmm = _mm_load_ps(&velocity_xyzw_stream_data[i]);
        __m128 result_xmm   = _mm_add_ps(position_xmm, velocity_xmm);
        _mm_store_ps(&position_xyzw_stream_data[i], result_xmm);
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        position_xyzw_stream_data[i] += velocity_xyzw_stream_data[i];
    }
#endif // USE_SSE2
#elif !defined(POSITION_LAYOUT_XYZW) && !defined(VELOCITY_LAYOUT_XYZW)
    float* position_x_stream_data = data.get_stream_data<float>(ParticleSystemStream::POSITION_X);
    float* velocity_x_stream_data = data.get_stream_data<float>(ParticleSystemStream::VELOCITY_X);

#ifdef USE_SSE2
    for (size_t i = 0; i < data.get_size(); i += 4) {
        __m128 position_xmm = _mm_load_ps(position_x_stream_data + i);
        __m128 velocity_xmm = _mm_load_ps(velocity_x_stream_data + i);
        __m128 result_xmm   = _mm_add_ps(position_xmm, velocity_xmm);
        _mm_store_ps(position_x_stream_data + i, result_xmm);
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        position_x_stream_data[i] += velocity_x_stream_data[i];
    }
#endif // USE_SSE2

    float* position_y_stream_data = data.get_stream_data<float>(ParticleSystemStream::POSITION_Y);
    float* velocity_y_stream_data = data.get_stream_data<float>(ParticleSystemStream::VELOCITY_Y);

#ifdef USE_SSE2
    for (size_t i = 0; i < data.get_size(); i += 4) {
        __m128 position_xmm = _mm_load_ps(position_y_stream_data + i);
        __m128 velocity_xmm = _mm_load_ps(velocity_y_stream_data + i);
        __m128 result_xmm   = _mm_add_ps(position_xmm, velocity_xmm);
        _mm_store_ps(position_y_stream_data + i, result_xmm);
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        position_y_stream_data[i] += velocity_y_stream_data[i];
    }
#endif // USE_SSE2

    float* position_z_stream_data = data.get_stream_data<float>(ParticleSystemStream::POSITION_Z);
    float* velocity_z_stream_data = data.get_stream_data<float>(ParticleSystemStream::VELOCITY_Z);

#ifdef USE_SSE2
    for (size_t i = 0; i < data.get_size(); i += 4) {
        __m128 position_xmm = _mm_load_ps(position_z_stream_data + i);
        __m128 velocity_xmm = _mm_load_ps(velocity_z_stream_data + i);
        __m128 result_xmm   = _mm_add_ps(position_xmm, velocity_xmm);
        _mm_store_ps(position_z_stream_data + i, result_xmm);
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        position_z_stream_data[i] += velocity_z_stream_data[i];
    }
#endif // USE_SSE2
#else
#error This combination is not supported.
#endif // defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW)
}

ParticleSystemStreamMask PositionParticleSystemUpdater::get_stream_mask() const {
#if defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW)
    return ParticleSystemStreamMask::POSITION_XYZW |
           ParticleSystemStreamMask::VELOCITY_XYZW;
#elif !defined(POSITION_LAYOUT_XYZW) && !defined(VELOCITY_LAYOUT_XYZW)
    return ParticleSystemStreamMask::POSITION_X |
           ParticleSystemStreamMask::POSITION_Y |
           ParticleSystemStreamMask::POSITION_Z |
           ParticleSystemStreamMask::VELOCITY_X |
           ParticleSystemStreamMask::VELOCITY_Y |
           ParticleSystemStreamMask::VELOCITY_Z;
#else
#error This combination is not supported.
#endif // defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW)
}
