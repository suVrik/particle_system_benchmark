#pragma once

enum class ParticleSystemStream {
#ifdef POSITION_LAYOUT_XYZW
    POSITION_XYZW,    // float4
#else
    POSITION_X,       // float
    POSITION_Y,       // float
    POSITION_Z,       // float
#endif // POSITION_LAYOUT_XYZW

#ifdef VELOCITY_LAYOUT_XYZW
    VELOCITY_XYZW,    // float4
#else
    VELOCITY_X,       // float
    VELOCITY_Y,       // float
    VELOCITY_Z,       // float
#endif // VELOCITY_LAYOUT_XYZW

#ifdef COLOR_LAYOUT_RGBA
    COLOR_RGBA,       // float4
#else
    COLOR_R,          // float
    COLOR_G,          // float
    COLOR_B,          // float
    COLOR_A,          // float
#endif // COLOR_LAYOUT_RGBA

    TOTAL_LIFETIME,   // float
    CURRENT_LIFETIME, // float
};

#if defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW) && defined(COLOR_LAYOUT_RGBA)
constexpr size_t PARTICLE_SYSTEM_STREAM_COUNT = 5;
#elif defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW) && !defined(COLOR_LAYOUT_RGBA)
constexpr size_t PARTICLE_SYSTEM_STREAM_COUNT = 8;
#elif !defined(POSITION_LAYOUT_XYZW) && !defined(VELOCITY_LAYOUT_XYZW) && defined(COLOR_LAYOUT_RGBA)
constexpr size_t PARTICLE_SYSTEM_STREAM_COUNT = 9;
#elif !defined(POSITION_LAYOUT_XYZW) && !defined(VELOCITY_LAYOUT_XYZW) && !defined(COLOR_LAYOUT_RGBA)
constexpr size_t PARTICLE_SYSTEM_STREAM_COUNT = 12;
#else
#error This combination is not supported.
#endif // defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW) && defined(COLOR_LAYOUT_RGBA)
