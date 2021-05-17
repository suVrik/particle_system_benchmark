#pragma once

#include "particle_system/auxiliary/enum.h"

#if defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW) && defined(COLOR_LAYOUT_RGBA)
enum class ParticleSystemStreamMask {
    NONE             = 0,
    POSITION_XYZW    = 1 << 0, // Always present.
    VELOCITY_XYZW    = 1 << 1,
    COLOR_RGBA       = 1 << 2,
    TOTAL_LIFETIME   = 1 << 3,
    CURRENT_LIFETIME = 1 << 4, // Always present.
};
#elif defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW) && !defined(COLOR_LAYOUT_RGBA)
enum class ParticleSystemStreamMask {
    NONE             = 0,
    POSITION_XYZW    = 1 << 0, // Always present.
    VELOCITY_XYZW    = 1 << 1,
    COLOR_R          = 1 << 2,
    COLOR_G          = 1 << 3,
    COLOR_B          = 1 << 4,
    COLOR_A          = 1 << 5,
    TOTAL_LIFETIME   = 1 << 6,
    CURRENT_LIFETIME = 1 << 7, // Always present.
};
#elif !defined(POSITION_LAYOUT_XYZW) && !defined(VELOCITY_LAYOUT_XYZW) && defined(COLOR_LAYOUT_RGBA)
enum class ParticleSystemStreamMask {
    NONE             = 0,
    POSITION_X       = 1 << 0, // Always present.
    POSITION_Y       = 1 << 1, // Always present.
    POSITION_Z       = 1 << 2, // Always present.
    VELOCITY_X       = 1 << 3,
    VELOCITY_Y       = 1 << 4,
    VELOCITY_Z       = 1 << 5,
    COLOR_RGBA       = 1 << 6,
    TOTAL_LIFETIME   = 1 << 7,
    CURRENT_LIFETIME = 1 << 8, // Always present.
};
#elif !defined(POSITION_LAYOUT_XYZW) && !defined(VELOCITY_LAYOUT_XYZW) && !defined(COLOR_LAYOUT_RGBA)
enum class ParticleSystemStreamMask {
    NONE             = 0,
    POSITION_X       = 1 << 0,  // Always present.
    POSITION_Y       = 1 << 1,  // Always present.
    POSITION_Z       = 1 << 2,  // Always present.
    VELOCITY_X       = 1 << 3,
    VELOCITY_Y       = 1 << 4,
    VELOCITY_Z       = 1 << 5,
    COLOR_R          = 1 << 6,
    COLOR_G          = 1 << 7,
    COLOR_B          = 1 << 8,
    COLOR_A          = 1 << 9,
    TOTAL_LIFETIME   = 1 << 10,
    CURRENT_LIFETIME = 1 << 11, // Always present.
};
#else
#error This combination is not supported.
#endif // defined(POSITION_LAYOUT_XYZW) && defined(VELOCITY_LAYOUT_XYZW) && defined(COLOR_LAYOUT_RGBA)

DEFINE_ENUM_BITMASK(ParticleSystemStreamMask);
