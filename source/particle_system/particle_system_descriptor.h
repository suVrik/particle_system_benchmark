#pragma once

#include "particle_system/particle_system_stream_mask.h"

#include <memory>
#include <vector>

class ParticleSystemData;
class ParticleSystemEmitter;
class ParticleSystemGenerator;
class ParticleSystemUpdater;

class ParticleSystemDescriptor {
public:
    ParticleSystemDescriptor(std::vector<std::unique_ptr<ParticleSystemEmitter>>&& emitters,
                             std::vector<std::unique_ptr<ParticleSystemGenerator>>&& generators,
                             std::vector<std::unique_ptr<ParticleSystemUpdater>>&& updaters,
                             float time);
    ~ParticleSystemDescriptor();

    const std::vector<std::unique_ptr<ParticleSystemEmitter>>& get_emitters() const {
        return m_emitters;
    }

    const std::vector<std::unique_ptr<ParticleSystemGenerator>>& get_generators() const {
        return m_generators;
    }

    const std::vector<std::unique_ptr<ParticleSystemUpdater>>& get_updaters() const {
        return m_updaters;
    }

    ParticleSystemStreamMask get_mask() const {
        return m_mask;
    }

    float get_time() const {
        return m_time;
    }

private:
    std::vector<std::unique_ptr<ParticleSystemEmitter>> m_emitters;
    std::vector<std::unique_ptr<ParticleSystemGenerator>> m_generators;
    std::vector<std::unique_ptr<ParticleSystemUpdater>> m_updaters;

    ParticleSystemStreamMask m_mask;

    float m_time;
};
