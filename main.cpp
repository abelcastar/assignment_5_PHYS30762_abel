// PHYS30762 Programming in C++
// Assignment 5
//=====================================================================
// Student ID   : 10832362
// Date     : 12/04/2025
//
// This program simulates photon-based interactions resulting from nuclear decay.
// It models stable and radioactive nuclei, with the latter emitting photons upon decay.
// These photons undergo interactions: photoelectric effect, Compton scattering, and 
// pair production. The program ensures validation for interactions and safe memory 
// management using smart pointers. Electrons can also radiate photons while conserving
// their kinetic energy. Please note each file has a description explaining design.
//=====================================================================


#include <iostream>
#include "stable.h"
#include "radioactive.h"
#include "photon.h"
#include "electron.h"

int main() {

  RadioactiveNucleus na(11, 22, "Na", 2.603);
  RadioactiveNucleus cs(55, 137, "Cs", 30.17);
  RadioactiveNucleus co(27, 60, "Co", 5.272);
  StableNucleus fe(26, 56, "Fe");

  na.decay();
  cs.decay();
  co.decay();
  fe.decay();  

  std::cout << "\n--- Attempt second decay on Na ---\n"<<std::endl;
  na.decay();

  std::cout << "\n--- Interactions Demonstration ---\n"<<std::endl;
  std::cout << "We have 6 total photons available to interact with.\n"<<std::endl;

  std::cout << "\n--- For one of the 511 keV Na photons ---\n"<<std::endl;
  compton_effect(na, 1, 120.0);
  Electron e_Na2 = photoelectric_effect(na, 1);
  std::cout << "\n--- Attempt to Compton scatter the photon that was just absorbed. ---\n"<<std::endl;
  compton_effect(na, 1, 120.0); 

  std::cout << "\n--- Attempt Pair Production on Cs photon[0] ---\n"<<std::endl;
  pair_production(cs, 0);
  std::cout << "\n--- Photoelectric on Cs photon instead ---\n"<<std::endl;
  Electron e_Cs1 = photoelectric_effect(cs, 0);

  std::cout << "\n--- Pair Production on Na 1274.5 keV photon ---\n"<<std::endl;
  auto electrons_from_Na = pair_production(na, 0);

  std::cout << "\n--- Pair Production on Co 1173 keV photon ---\n"<<std::endl;
  auto electrons_from_Co = pair_production(co, 0);

  std::cout << "\n--- Absorb remaining photons using Photoelectric ---\n"<<std::endl;
  photoelectric_effect(co, 1);  
  photoelectric_effect(na, 2);
  std::cout << "\n--- Absorbing a non existent photon ---\n"<<std::endl;
  photoelectric_effect(na, 3); 

  std::cout << "\n--- Radiation from one pair-produced electron from Na 1274.5 keV photon---\n"<<std::endl;
  Electron& e = *electrons_from_Na[0]; 

  e.radiate(2, 100.0);
  e.print_data();

  e.radiate(2, 25.0);
  e.print_data();
  
  return 0;
}
