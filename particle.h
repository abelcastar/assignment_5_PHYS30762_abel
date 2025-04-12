// This file defines the base Particle class with a single energy property.
// It enforces non-negative energy, provides virtual printing behavior,
// and serves as the abstract base for specific particle types.
// Again kept all in the same.h file because this is a fully abstract class
// and despite validation a 4 line .cpp file was useless.
//=====================================================================

#pragma once
#include <iostream>
#include <cmath> 

class Particle {
private:
    double energy;

public:
  Particle() = delete; // Prevent invalid construction of Particle objects

  Particle(double energy_in) {set_energy(energy_in);}

  virtual ~Particle() = default;

  double get_energy() const { return energy;}
  void set_energy(double energy_in)
  {
    if(energy_in < 0.0) {std::cerr<<"Energy cannot be negative. "
    <<"Taking absolute value: "<<energy_in<<" taken as "<<std::abs(energy_in)<<"\n"<<std::endl;
    energy_in = std::abs(energy_in);}
    energy = energy_in;
  }
    virtual void print_data() const = 0;
};
