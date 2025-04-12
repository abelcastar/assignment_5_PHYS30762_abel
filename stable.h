// Class for a stable nucleus kept all in .h file since a .cpp of 8 lines seemed redundant.
//=====================================================================


#pragma once
#include "nucleus.h"
#include <iostream>
#include <stdexcept>

class StableNucleus : public Nucleus {
public:
  StableNucleus(int atomic_number_in, int atomic_mass_in, const std::string& type_in)
    : Nucleus(atomic_number_in, atomic_mass_in, type_in) {}

  void decay() override {
    std::cerr<<"Decay attempt on "<<get_type()<<" failed: Stable nucleus cannot decay.\n"
    <<std::endl;}

  void print_data() const override {
    std::cout<<"\nStable Nucleus: "<<get_type()<<" (Z="<<get_atomic_number()<<", A="
    <<get_atomic_mass()<<")\n"<<std::endl;}
};
