// This header defines the Electron class, derived from the abstract Particle base class.
// The Electron class models an electron's kinetic behavior, allows user-driven radiation 
// of photons (with energy tracking), and supports interaction with other particle types.
// Photons emitted by an electron are tracked using smart pointers to ensure safe memory 
// management, and functionality includes kinetic energy checks and emission limits.

#pragma once
#include "particle.h"
#include <vector>
#include <memory>
#include <iostream>

// Forward declaration of Photon to avoid circular dependency issues
class Photon;

class Electron : public Particle {
private:
  std::vector<std::unique_ptr<Photon>> emitted_photons;

public:
  // Constants (needed in pair production)
  static constexpr double rest_mass = 0.511; //in MeV
  static constexpr double PI = 3.14159265358979323846;

  // Constructor sets initial kinetic energy
  Electron(double energy) : Particle(energy) {}

  // Getter
   const std::vector<std::unique_ptr<Photon>>& get_emitted_photons() const;

  // Radiate function (defined in electron.cpp)
  std::vector<std::unique_ptr<Photon>> radiate(int number_of_photons, double photon_energy_keV);

  // Print electron data (defined in electron.cpp)
  void print_data() const override;
};
