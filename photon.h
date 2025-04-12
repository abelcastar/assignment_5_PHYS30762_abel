// This file defines the Photon class, derived from Particle, and provides
// interaction functions like photoelectric effect, Compton scattering, 
// and pair production. Photons are emitted from radioactive nuclei and 
// can interact with matter to produce electrons.

// Note:
// Electrons produced from photon interactions are not owned by the Photon.
// Instead, they are returned as independent objects, reflecting a more 
// realistic particle behavior, I deviated from the brief because I thought
// this to be more modular interaction logic.
//=====================================================================
//=====================================================================

#pragma once
#include "particle.h"
#include "electron.h"
#include "nucleus.h"
#include <iostream>
#include <vector>
#include <memory>

class Photon : public Particle {
public:
  Photon(double energy) : Particle(energy) {}

  // Print photon energies (defined in photon.cpp)
  void print_data() const override;

  // Interactions friend functions (defined in photon.cpp)
  friend Electron photoelectric_effect(const Photon& selected_photon); 
  friend void compton_effect(Photon& selected_photon, double angle_in_deg);
  friend std::vector<std::unique_ptr<Electron>> pair_production(const Photon& selected_photon);
};

// Interaction wrappers for nucleus-level (defined in photon.cpp)
Electron photoelectric_effect(const Nucleus& nucleus, size_t photon_index);
void compton_effect(const Nucleus& nucleus, size_t photon_index, double angle_in_deg);
std::vector<std::unique_ptr<Electron>> pair_production(const Nucleus& nucleus, size_t photon_index);

