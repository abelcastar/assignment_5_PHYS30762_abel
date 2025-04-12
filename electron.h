#pragma once
#include "particle.h"
#include <vector>
#include <memory>
#include <iostream>

// Forward declare Photon instead of including photon.h
class Photon;

class Electron : public Particle {
private:
    std::vector<std::unique_ptr<Photon>> emitted_photons;

public:
    // Electron rest mass in MeV (constant reference for validation in pair production later)
    static constexpr double rest_mass = 0.511;
    static constexpr double PI = 3.14159265358979323846;

    // Constructor: set initial kinetic energy (not rest mass)
    Electron(double energy)
        : Particle(energy) {}

    // User-controlled photon emission
    std::vector<std::unique_ptr<Photon>> radiate(int number_of_photons, double photon_energy_keV);

    // getter for emitted photons (read-only)
     const std::vector<std::unique_ptr<Photon>>& get_emitted_photons() const;


    void print_data() const override;
};
