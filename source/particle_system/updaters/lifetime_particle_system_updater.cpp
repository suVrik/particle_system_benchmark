#include "particle_system/updaters/lifetime_particle_system_updater.h"
#include "particle_system/particle_system_data.h"
#include "particle_system/particle_system_stream.h"

#ifdef USE_SSE2
#include <emmintrin.h>
#endif // USE_SSE2

void LifetimeParticleSystemUpdater::update(ParticleSystemData& data, float elapsed_time) const {
    float* current_lifetime_stream_data = data.get_stream_data<float>(ParticleSystemStream::CURRENT_LIFETIME);

#ifdef USE_SSE2
    __m128 elapsed_time_xmm = _mm_set1_ps(-elapsed_time);

    for (size_t i = 0; i < data.get_size(); i += 4) {
        _mm_store_ps(current_lifetime_stream_data + i, _mm_add_ps(_mm_load_ps(current_lifetime_stream_data + i), elapsed_time_xmm));
    }
#else
    for (size_t i = 0; i < data.get_size(); i++) {
        current_lifetime_stream_data[i] -= elapsed_time;
    }
#endif // USE_SSE2
}

ParticleSystemStreamMask LifetimeParticleSystemUpdater::get_stream_mask() const {
    return ParticleSystemStreamMask::CURRENT_LIFETIME;
}
