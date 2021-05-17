#pragma once

#include "particle_system/particle_system_stream_mask.h"

class ParticleSystemData;

class ParticleSystemUpdater {
public:
    virtual ~ParticleSystemUpdater() = default;

    virtual void update(ParticleSystemData& data, float elapsed_time) const = 0;

    virtual ParticleSystemStreamMask get_stream_mask() const = 0;
};
