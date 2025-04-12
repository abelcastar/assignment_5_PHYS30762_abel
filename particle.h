#pragma once
#include <iostream>
#include <cmath> 

class Particle {
private:
    double energy;

public:
    Particle() = delete;

    Particle(double energy_in) {
        set_energy(energy_in);
    }

    virtual ~Particle() = default;

    double get_energy() const { return energy; }
    void set_energy(double e) {
            if (e < 0.0) {
                std::cerr << "Energy cannot be negative. "
                        << "Taking absolute value: " << e << " -> " << std::abs(e) << "\n";
                e = std::abs(e);
            }
            energy = e;
        }
    virtual void print_data() const = 0;
};
