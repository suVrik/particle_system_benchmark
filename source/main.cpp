#include "particle_system/emitters/over_time_particle_system_emitter.h"
#include "particle_system/generators/box_position_particle_system_generator.h"
#include "particle_system/generators/lifetime_particle_system_generator.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_descriptor.h"
#include "particle_system/particle_system_primitive.h"
#include "particle_system/updaters/color_over_lifetime_particle_system_updater.h"
#include "particle_system/updaters/lifetime_particle_system_updater.h"
#include "particle_system/updaters/position_particle_system_updater.h"
#include "particle_system/updaters/velocity_over_lifetime_particle_system_updater.h"

#include <chrono>
#include <iostream>

const size_t PRIMTIIVE_COUNTS[] = {
    10,
    25,
    50,
    75,
    100,
    250,
    500,
    750,
    1000,
    1500,
    2000,
    3000,
    5000,
    10000,
    25000,
};

constexpr float PARTICLES_PER_SECOND     = 200.f;
constexpr float PARTICLE_LIFETIME        = 2.f;
constexpr float PARTICLE_SYSTEM_LIFETIME = 20.f;
constexpr float ELAPSED_TIME             = 0.015f;

int main(int argc, char* argv[]) {
    std::vector<std::unique_ptr<ParticleSystemEmitter>> emitters;
    emitters.reserve(1);
    emitters.push_back(std::unique_ptr<ParticleSystemEmitter>(new OverTimeParticleSystemEmitter(PARTICLES_PER_SECOND, PARTICLES_PER_SECOND)));

    std::vector<std::unique_ptr<ParticleSystemGenerator>> generators;
    generators.reserve(2);
    generators.push_back(std::unique_ptr<ParticleSystemGenerator>(new BoxPositionParticleSystemGenerator(float3(0.5f), float3(1.f))));
    generators.push_back(std::unique_ptr<ParticleSystemGenerator>(new LifetimeParticleSystemGenerator(PARTICLE_LIFETIME, PARTICLE_LIFETIME)));

    std::vector<std::unique_ptr<ParticleSystemUpdater>> updaters;
    updaters.reserve(4);
    updaters.push_back(std::unique_ptr<ParticleSystemUpdater>(new VelocityOverLifetimeParticleSystemUpdater(float3(-1.f), float3(1.f))));
    updaters.push_back(std::unique_ptr<ParticleSystemUpdater>(new ColorOverLifetimeParticleSystemUpdater(float4(1.f), float4(0.f))));
    updaters.push_back(std::unique_ptr<ParticleSystemUpdater>(new PositionParticleSystemUpdater()));
    updaters.push_back(std::unique_ptr<ParticleSystemUpdater>(new LifetimeParticleSystemUpdater()));

    ParticleSystemDescriptor descriptor(
        std::move(emitters),
        std::move(generators),
        std::move(updaters),
        PARTICLE_SYSTEM_LIFETIME
    );

#ifdef CONTIGUOUS_PRIMITIVE_DATA
    for (size_t primitive_count : PRIMTIIVE_COUNTS) {
        std::vector<std::unique_ptr<ParticleSystemPrimitive>> primitives;
        primitives.reserve(primitive_count);

        for (size_t i = 0; i < primitive_count; i++) {
            // We can pass any matrix for benchmark, all the math will be performed anyway.
            primitives.push_back(std::make_unique<ParticleSystemPrimitive>(float4x4()));
        }

        ParticleSystemData data(descriptor, std::move(primitives));

        // We're not measuring `_aligned_realloc` in this benchmark.
        data.reserve(primitive_count * 500);

        {
            auto before = std::chrono::high_resolution_clock::now();

            for (float t = 0.f; t < PARTICLE_SYSTEM_LIFETIME; t += ELAPSED_TIME) {
                data.update(ELAPSED_TIME);
            }

            auto after = std::chrono::high_resolution_clock::now();

            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count() << std::endl;
        }
    }
#else
    for (size_t primitive_count : PRIMTIIVE_COUNTS) {
        std::vector<ParticleSystemData> datas;
        datas.reserve(primitive_count);

        for (size_t i = 0; i < primitive_count; i++) {
            ParticleSystemData& data = datas.emplace_back(descriptor, std::make_unique<ParticleSystemPrimitive>(float4x4()));

            // We're not measuring `_aligned_realloc` in this benchmark.
            data.reserve(500);
        }

        {
            auto before = std::chrono::high_resolution_clock::now();

            for (float t = 0.f; t < PARTICLE_SYSTEM_LIFETIME; t += ELAPSED_TIME) {
                for (ParticleSystemData& data : datas) {
                    data.update(ELAPSED_TIME);
                }
            }

            auto after = std::chrono::high_resolution_clock::now();

            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count() << std::endl;
        }
    }
#endif // CONTIGUOUS_PRIMITIVE_DATA
}
