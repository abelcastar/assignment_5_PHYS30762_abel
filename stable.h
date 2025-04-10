#pragma once
#include "nucleus.h"
#include <iostream>
#include <stdexcept>

class StableNucleus : public Nucleus {
public:
    // Constructor: forward args to base class constructor
    StableNucleus(int atomic_number_in, int atomic_mass_in, const std::string& type_in)
        : Nucleus(atomic_number_in, atomic_mass_in, type_in) {}

    // Override decay — this shouldn't be allowed
    void decay() override {
        std::cerr << "Decay attempt on " << get_type()
                << " failed: Stable nucleus cannot decay.\n" << std::endl;
    }


    // Override print_data to show info clearly
    void print_data() const override {
        std::cout << "\nStable Nucleus: " << get_type()
                  << " (Z=" << get_atomic_number()
                  << ", A=" << get_atomic_mass() << ")\n" << std::endl;
    }
};
