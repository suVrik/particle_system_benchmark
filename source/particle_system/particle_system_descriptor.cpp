#include "particle_system/particle_system_descriptor.h"
#include "particle_system/emitters/particle_system_emitter.h"
#include "particle_system/generators/particle_system_generator.h"
#include "particle_system/updaters/particle_system_updater.h"

ParticleSystemDescriptor::ParticleSystemDescriptor(std::vector<std::unique_ptr<ParticleSystemEmitter>>&& emitters,
                                                   std::vector<std::unique_ptr<ParticleSystemGenerator>>&& generators,
                                                   std::vector<std::unique_ptr<ParticleSystemUpdater>>&& updaters,
                                                   float time)
    : m_emitters(std::move(emitters))
    , m_generators(std::move(generators))
    , m_updaters(std::move(updaters))
    , m_mask(ParticleSystemStreamMask::NONE)
    , m_time(time)
{
    for (std::unique_ptr<ParticleSystemGenerator>& generator : m_generators) {
        m_mask |= generator->get_stream_mask();
    }

    for (std::unique_ptr<ParticleSystemUpdater>& updater : m_updaters) {
        m_mask |= updater->get_stream_mask();
    }
}

ParticleSystemDescriptor::~ParticleSystemDescriptor() = default;
