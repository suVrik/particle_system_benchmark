#pragma once

#include "particle_system/particle_system_stream_mask.h"

class ParticleSystemData;
class ParticleSystemPrimitive;

class ParticleSystemGenerator {
public:
    virtual ~ParticleSystemGenerator() = default;

    virtual void generate(ParticleSystemData& data, ParticleSystemPrimitive& primitive, size_t begin_index, size_t end_index) const = 0;
    
    virtual ParticleSystemStreamMask get_stream_mask() const = 0;
};
