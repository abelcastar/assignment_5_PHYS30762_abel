#pragma once
#include <iostream>

class Particle {
private:
    double energy;

public:
    Particle() = delete;

    Particle(double energy)
        : energy(energy) {}

    virtual ~Particle() = default;

    double get_energy() const { return energy; }
    void set_energy(double e) { energy = e; }

    virtual void print_data() const = 0;
};
