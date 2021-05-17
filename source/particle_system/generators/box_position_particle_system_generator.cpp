#include "particle_system/generators/box_position_particle_system_generator.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_primitive.h"
#include "particle_system/particle_system_stream.h"

#ifdef USE_SSE2
#include <emmintrin.h>
#include <immintrin.h>
#endif // USE_SSE2

BoxPositionParticleSystemGenerator::BoxPositionParticleSystemGenerator(const float3& inner_size, const float3& outer_size)
#ifdef USE_SSE2
    : m_size_range(outer_size - inner_size, 0.f)
    , m_size_offset(inner_size, 0.f)
#else
    : m_size_range(outer_size - inner_size)
    , m_size_offset(inner_size)
#endif // USE_SSE2
{
}

void BoxPositionParticleSystemGenerator::generate(ParticleSystemData& data, ParticleSystemPrimitive& primitive, size_t begin_index, size_t end_index) const {
    Random& random = data.get_random();

    const float4x4& global_transform = primitive.get_global_transform();

#ifdef POSITION_LAYOUT_XYZW
    float4* position_xyzw_stream_data = data.get_stream_data<float4>(ParticleSystemStream::POSITION_XYZW);

#ifdef USE_SSE2
    __m128 size_range_xmm = _mm_load_ps(&m_size_range);
    __m128 size_offset_xmm = _mm_load_ps(&m_size_offset);

    __m128 global_transform_row0_xmm = _mm_load_ps(&global_transform.rows[0]);
    __m128 global_transform_row3_xmm = _mm_load_ps(&global_transform.rows[3]);
    __m128 global_transform_row1_xmm = _mm_load_ps(&global_transform.rows[1]);
    __m128 global_transform_row2_xmm = _mm_load_ps(&global_transform.rows[2]);

    for (size_t i = begin_index; i < end_index; i++) {
        __m128 local_point_xmm = random.rand_simd4();
        local_point_xmm = _mm_mul_ps(local_point_xmm, size_range_xmm);
        local_point_xmm = _mm_add_ps(local_point_xmm, size_offset_xmm);

        __m128 local_point_x_xmm = _mm_permute_ps(local_point_xmm, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 global_point_xmm = _mm_fmadd_ps(local_point_x_xmm, global_transform_row0_xmm, global_transform_row3_xmm);
        __m128 local_point_y_xmm = _mm_permute_ps(local_point_xmm, _MM_SHUFFLE(1, 1, 1, 1));
        global_point_xmm = _mm_fmadd_ps(local_point_y_xmm, global_transform_row1_xmm, global_point_xmm);
        __m128 local_point_z_xmm = _mm_permute_ps(local_point_xmm, _MM_SHUFFLE(2, 2, 2, 2));
        global_point_xmm = _mm_fmadd_ps(local_point_z_xmm, global_transform_row2_xmm, global_point_xmm);

        _mm_store_ps(&position_xyzw_stream_data[i], global_point_xmm);
    }
#else
    for (size_t i = begin_index; i < end_index; i++) {
        float3 local_point = random.rand_float3() * m_size_range + m_size_offset;
        float3 global_point = local_point * global_transform;

        position_xyzw_stream_data[i] = float4(global_point, 0.f);
    }
#endif // USE_SSE2
#else
    float* position_x_stream_data = data.get_stream_data<float>(ParticleSystemStream::POSITION_X);
    float* position_y_stream_data = data.get_stream_data<float>(ParticleSystemStream::POSITION_Y);
    float* position_z_stream_data = data.get_stream_data<float>(ParticleSystemStream::POSITION_Z);

#ifdef USE_SSE2
    __m128 size_range_xmm  = _mm_load_ps(&m_size_range);
    __m128 size_offset_xmm = _mm_load_ps(&m_size_offset);

    __m128 global_transform_row0_xmm = _mm_load_ps(&global_transform.rows[0]);
    __m128 global_transform_row3_xmm = _mm_load_ps(&global_transform.rows[3]);
    __m128 global_transform_row1_xmm = _mm_load_ps(&global_transform.rows[1]);
    __m128 global_transform_row2_xmm = _mm_load_ps(&global_transform.rows[2]);

    for (size_t i = begin_index; i < end_index; i++) {
        __m128 local_point_xmm = random.rand_simd4();
        local_point_xmm = _mm_mul_ps(local_point_xmm, size_range_xmm);
        local_point_xmm = _mm_add_ps(local_point_xmm, size_offset_xmm);

        __m128 local_point_x_xmm = _mm_permute_ps(local_point_xmm, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 global_point_xmm  = _mm_fmadd_ps(local_point_x_xmm, global_transform_row0_xmm, global_transform_row3_xmm);
        __m128 local_point_y_xmm = _mm_permute_ps(local_point_xmm, _MM_SHUFFLE(1, 1, 1, 1));
        global_point_xmm = _mm_fmadd_ps(local_point_y_xmm, global_transform_row1_xmm, global_point_xmm);
        __m128 local_point_z_xmm = _mm_permute_ps(local_point_xmm, _MM_SHUFFLE(2, 2, 2, 2));
        global_point_xmm = _mm_fmadd_ps(local_point_z_xmm, global_transform_row2_xmm, global_point_xmm);

        position_x_stream_data[i] = _mm_cvtss_f32(_mm_permute_ps(global_point_xmm, _MM_SHUFFLE(0, 0, 0, 0)));
        position_y_stream_data[i] = _mm_cvtss_f32(_mm_permute_ps(global_point_xmm, _MM_SHUFFLE(1, 1, 1, 1)));
        position_z_stream_data[i] = _mm_cvtss_f32(_mm_permute_ps(global_point_xmm, _MM_SHUFFLE(2, 2, 2, 2)));
    }
#else
    for (size_t i = begin_index; i < end_index; i++) {
        float3 local_point = random.rand_float3() * m_size_range + m_size_offset;
        float3 global_point = local_point * primitive.get_global_transform();

        position_x_stream_data[i] = global_point.x;
        position_y_stream_data[i] = global_point.y;
        position_z_stream_data[i] = global_point.z;
    }
#endif // USE_SSE2
#endif // POSITION_LAYOUT_XYZW
}

ParticleSystemStreamMask BoxPositionParticleSystemGenerator::get_stream_mask() const {
#ifdef POSITION_LAYOUT_XYZW
    return ParticleSystemStreamMask::POSITION_XYZW;
#else
    return ParticleSystemStreamMask::POSITION_X |
           ParticleSystemStreamMask::POSITION_Y |
           ParticleSystemStreamMask::POSITION_Z;
#endif // POSITION_LAYOUT_XYZW
}
