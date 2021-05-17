#pragma once

class ParticleSystemData;
class ParticleSystemPrimitive;

class ParticleSystemEmitter {
public:
    virtual ~ParticleSystemEmitter() = default;

    virtual size_t emit(ParticleSystemData& data, ParticleSystemPrimitive& primitive, float elapsed_time) const = 0;
};
