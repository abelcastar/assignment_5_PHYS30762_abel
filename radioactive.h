// This file defines the RadioactiveNucleus class, which inherits from 
// Nucleus and models decay behavior. It uses smart pointers to track 
// emitted photons, enforces decay constraints, and implements the Rule of 5.
//=====================================================================

#pragma once
#include "nucleus.h"
#include "photon.h"

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class RadioactiveNucleus : public Nucleus {
private:
  double half_life;
  bool has_decayed;
  std::vector<std::unique_ptr<Photon>> emitted_photons;

public:
  RadioactiveNucleus(int atomic_number_in, int atomic_mass_in, const std::string& type_in, double half_life_in);

  // Rule of 5 operators(defined in radioactive.cpp)
  ~RadioactiveNucleus() override;
  RadioactiveNucleus(const RadioactiveNucleus& other);
  RadioactiveNucleus& operator=(const RadioactiveNucleus& other);
  RadioactiveNucleus(RadioactiveNucleus&& other) noexcept;
  RadioactiveNucleus& operator=(RadioactiveNucleus&& other) noexcept;

  // Overrides from Nucleus (defined in radioactive.cpp)
  void decay() override;
  void print_data() const override;

  // Getters
  double get_half_life() const {return half_life;}
  bool is_decayed()      const {return has_decayed;}
  const std::vector<std::unique_ptr<Photon>>& get_emitted_photons() const {return emitted_photons;}
};
