#pragma once

#include "particle_system/updaters/particle_system_updater.h"

class LifetimeParticleSystemUpdater : public ParticleSystemUpdater {
public:
    void update(ParticleSystemData& data, float elapsed_time) const override;

    ParticleSystemStreamMask get_stream_mask() const override;
};
