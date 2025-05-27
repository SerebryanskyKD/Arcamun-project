#pragma once
#include <random>

class Probability {
public:
    static Probability& instance();

    void setSeed(unsigned int seed);
    bool roll(float chancePercent);
    int range(int min, int max);
    float rangef(float min, float max);
private:
    Probability();
    std::mt19937 rng;
};
