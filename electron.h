#pragma once
#include "particle.h"
#include <vector>
#include <memory>
#include <iostream>

// 🔧 Forward declare Photon instead of including photon.h
class Photon;

class Electron : public Particle {
private:
    std::vector<std::unique_ptr<Photon>> emitted_photons;

public:
    // Electron rest mass in MeV (constant reference for validation in pair production later)
    static constexpr double rest_mass = 0.511;

    // Constructor: set initial kinetic energy (not rest mass)
    Electron(double energy)
        : Particle(energy) {}

    // Radiate a photon (returns ownership to caller)
    std::unique_ptr<Photon> radiate();

    // Access emitted photons (read-only)
    const std::vector<std::unique_ptr<Photon>>& get_emitted_photons() const {
        return emitted_photons;
    }

    // Print details
    void print_data() const override {
        std::cout << "Electron:\n"
                  << "  Energy: " << get_energy() << " keV\n"
                  << "  Rest mass: " << rest_mass << " MeV\n"
                  << "  Photons emitted: " << emitted_photons.size() << "\n"
                  << std::endl;
    }
};
