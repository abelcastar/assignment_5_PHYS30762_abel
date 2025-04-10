#pragma once
#include "particle.h"
#include "photon.h"
#include <vector>
#include <memory>
#include <iostream>

class Electron : public Particle {
private:
    std::vector<std::shared_ptr<Photon>> emitted_photons;

public:
    // Electron rest mass in MeV (constant reference for validation in pair production later)
    static constexpr double rest_mass = 0.511;

    // Constructor: set initial kinetic energy (not rest mass)
    Electron(double energy)
        : Particle(energy) {}

    // Add a photon to this electron's emission list no checking for pair production yet
    void add_emitted_photon(std::shared_ptr<Photon> photon) {
        emitted_photons.emplace_back(std::move(photon));
    }

    const std::vector<std::shared_ptr<Photon>>& get_emitted_photons() const {
        return emitted_photons;
    }

    // Override print_data()
    void print_data() const override {
        std::cout << "Electron:\n"
                  << "  Energy: " << get_energy() << " keV\n"
                  << "  Rest mass: " << rest_mass << " MeV\n"
                  << "  Photons emitted: " << emitted_photons.size() << "\n"
                  << std::endl;
    }

    // Friend function for external radiation process
    friend std::shared_ptr<Photon> radiate(Electron& e);
    std::shared_ptr<Photon> radiate();

};
