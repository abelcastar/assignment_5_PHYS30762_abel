// This file shows the logic for the interaction functions:
//   - Photoelectric effect
//   - Compton scattering
//   - Pair production
//
// It includes shared validation logic to ensure that interactions are only applied 
// to photons that exist (i.e. belong to a radioactive nucleus that has decayed).
//
// Wrapper functions such as `photoelectric_effect(const Nucleus&, size_t)` ensure
// proper validation before calling the function logic. This avoids repetition
// (DRY principle) and keeps all interaction rules in a single place.
//=====================================================================

#include "photon.h"
#include "electron.h"
#include "radioactive.h"
#include <cmath>
#include <iostream>

// Helper function for validating interactions
static Photon* validate_interaction(const Nucleus& nucleus, size_t index, const std::string& interaction)
{const auto* radioactive_ptr = dynamic_cast<const RadioactiveNucleus*>(&nucleus);
  
  if(!radioactive_ptr) 
  {
    std::cerr<<"[Warning] "<<interaction<<": interaction only valid on radioactive nuclei.\n"<<std::endl;
    return nullptr;
  }

  if(!radioactive_ptr->is_decayed()) 
  {
    std::cerr<<"[Warning] "<<interaction<<": nucleus has not decayed yet.\n"<<std::endl;
    return nullptr;
  }

  const auto& photons = radioactive_ptr->get_emitted_photons();

  if(index >= photons.size())
  {
    std::cerr<<"[Warning] "<<interaction<<": invalid photon index "<<index<<". Only "<<photons.size()<<" photons available.\n"<<std::endl;
    return nullptr;
  }

  Photon* photon = photons[index].get();
  
  if(photon->get_energy() <= 0.0)
  {
    std::cerr<<"[Warning] "<<interaction<<": cannot interact with photon of 0 keV (interaction skipped).\n"<<std::endl;
    return nullptr;
  }

  return photon;
}

// Photon print function
void Photon::print_data() const {std::cout<<"Photon with energy "<<get_energy()<<" keV was emitted.\n"<<std::endl;}


Electron photoelectric_effect(const Photon& selected_photon)
{
  std::cout<<"[Photoelectric Effect called]\n"<<std::endl;
  std::cout<<"  Photon with energy "<<selected_photon.get_energy()<<" keV fully absorbed (energy set to 0 keV).\n"<<std::endl;
  std::cout<<"  One electron emitted with: "<<selected_photon.get_energy()<<"keV (Note: Work function ignored since highest possible ~ 6eV)\n"<<std::endl;
  const_cast<Photon&>(selected_photon).set_energy(0.0);  // Mark as "absorved"

  return Electron(selected_photon.get_energy());
}

void compton_effect(Photon& selected_photon, double angle_in_deg)
{
  double angle_in_rad = angle_in_deg * Electron::PI / 180.0;
  double initial_energy = selected_photon.get_energy();
  double rest_mass_keV = Electron::rest_mass * 1000.0;

  double scattered_energy = initial_energy / (1 + (initial_energy / rest_mass_keV) * (1 - std::cos(angle_in_rad)));
  selected_photon.set_energy(scattered_energy);

  std::cout<<"[Compton Scattering called]\n"<<std::endl;
  std::cout<<"  Incoming photon energy: "<<initial_energy<<" keV\n"<<std::endl;
  std::cout<<"  Scattering angle: "<<angle_in_deg<<" degrees\n"<<std::endl;
  std::cout<<"  Photon energy after scattering: "<<scattered_energy<<" keV\n\n"<<std::endl;
}

std::vector<std::unique_ptr<Electron>> pair_production(const Photon& selected_photon)
{
  constexpr double rest_mass_keV = Electron::rest_mass * 1000;

  if(selected_photon.get_energy() < 2 * rest_mass_keV)
  {
    std::cout<<"Pair production failed: photon energy ("<<selected_photon.get_energy()
    <<" keV) is too low.\nRequires at least "<<2 * rest_mass_keV<<" keV.\n"<<std::endl;
    return {};
  }

  double energy_per_electron = selected_photon.get_energy() / 2.0;
  auto electron_1 = std::make_unique<Electron>(energy_per_electron);
  auto electron_2 = std::make_unique<Electron>(energy_per_electron);

  std::cout<<"Pair production successful from photon ("<<selected_photon.get_energy()<<" keV):\n"<<std::endl;
  electron_1->print_data();
  electron_2->print_data(); //should technically be a positron brief just said make a vector of electrons.

  std::vector<std::unique_ptr<Electron>> result;
  result.push_back(std::move(electron_1));
  result.push_back(std::move(electron_2));
  const_cast<Photon&>(selected_photon).set_energy(0.0);  // Mark as "absorved"

  return result;
}

Electron photoelectric_effect(const Nucleus& nucleus, size_t index) {
  Photon* photon = validate_interaction(nucleus, index, "Photoelectric Effect");
  if(!photon)
  {
    std::cerr<<"[Follow Up Warning] Dummy Electron created (0 keV) the interaction was skipped.\n"<<std::endl;
    return Electron(0.0);
  }

  return photoelectric_effect(*photon);
}

void compton_effect(const Nucleus& nucleus, size_t index, double angle_in_deg)
{
  Photon* photon = validate_interaction(nucleus, index, "Compton Scattering");
  if(!photon) return;

  compton_effect(*photon, angle_in_deg);
}

std::vector<std::unique_ptr<Electron>> pair_production(const Nucleus& nucleus, size_t index)
{
  Photon* photon = validate_interaction(nucleus, index, "Pair Production");
  if(!photon) return {};

  return pair_production(*photon);
}

