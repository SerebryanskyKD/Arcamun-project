#pragma once
#include <random>

class Probability {
public:
    static Probability& instance();
    bool roll(float chancePercent);
    int range(int min, int max);

private:
    Probability();
    std::mt19937 rng;
};
