// This file implements the Electron class methods defined in electron.h.
// It provides user-driven photon emission via the radiate() method, which ensures
// energy conservation. Photons are stored using smart pointers to track ownership 
// and prevent memory leaks. The print_data() function displays kinetic energy and 
// photon emission details.
//=========================================================================================

#include "electron.h"
#include "photon.h"
#include <iostream>

std::vector<std::unique_ptr<Photon>> Electron::radiate(int number_of_photons, double photon_energy_keV)
{
  std::vector<std::unique_ptr<Photon>> emitted_now;

  // Radiate photons ifenergy allows

  double total_required_energy = number_of_photons * photon_energy_keV;
  double current_energy = get_energy();

  std::cout<<"[Radiate] Request: "<<number_of_photons<<" photon(s) with "
       <<photon_energy_keV<<" keV each from electron with "<<current_energy<<" keV.\n"<<std::endl;

  if(number_of_photons <= 0 || photon_energy_keV <= 0.0)
  {
    std::cerr<<"[Error] Invalid input: number and energy must be positive.\n"<<std::endl;
    return emitted_now;
  }

  if(total_required_energy > current_energy)
  {
    std::cerr<<"[Radiate] Failed: Not enough energy to radiate "<<number_of_photons<<" photon(s) at "
      <<photon_energy_keV<<" keV each (Total: "<<total_required_energy<<" keV, Available: "<<current_energy<<" keV).\n"<<std::endl;
    return emitted_now;
  }

  for(int index = 0; index < number_of_photons; ++index)
  {
    auto photon = std::make_unique<Photon>(photon_energy_keV);
    emitted_now.emplace_back(std::make_unique<Photon>(*photon));    // Copy for internal record
    emitted_photons.emplace_back(std::make_unique<Photon>(*photon));  // Store for tracking
  }

  set_energy(current_energy - total_required_energy);

  std::cout<<"[Radiate] Successful: "<<number_of_photons<<" photon(s) emitted.\n"
    <<"  Remaining electron energy: "<<get_energy()<<" keV\n"<<std::endl;

  return emitted_now;
}

// Return reference to internally stored emitted photons
const std::vector<std::unique_ptr<Photon>>& Electron::get_emitted_photons() const {return emitted_photons;}

// Print function
void Electron::print_data() const
{
  std::cout<<"Electron:\n"<<"  Kinetic Energy: "<<get_energy()<<" keV\n"
       <<"  Rest Mass: "<<rest_mass<<" MeV\n"<<"  Photons emitted: "<<emitted_photons.size();

  if(!emitted_photons.empty())
  {
    std::cout<<" \n  Energies in keV: [";
    for(size_t index = 0; index < emitted_photons.size(); ++index)
    {
      std::cout<<emitted_photons[index]->get_energy();
      if(index != emitted_photons.size() - 1) {std::cout<<", ";}
    }
    std::cout<<"]"<<std::endl;
  }

  std::cout<<"\n"<<std::endl;
}
