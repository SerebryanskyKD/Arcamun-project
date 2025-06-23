#include "Probability.h"
#include <chrono>

Probability::Probability() {
    rng.seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
}

Probability& Probability::instance() {
    static Probability instance;
    return instance;
}

bool Probability::roll(float chancePercent) {
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);
    return dist(rng) < chancePercent;
}

int Probability::range(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}
