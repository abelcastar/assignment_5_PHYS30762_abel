// Abstract base class representing a nucleus kept all in .h file since a .cpp of 2 lines seemed redundant.
//=====================================================================


#pragma once
#include <string>

class Nucleus {
private:
  int atomic_number;
  int atomic_mass;
  std::string nucleus_type;

public:
  Nucleus() = delete; // Prevent invalid construction of Nucleus objects

  Nucleus(int atomic_number_in, int atomic_mass_in, const std::string& type_in)
    : atomic_number(atomic_number_in), atomic_mass(atomic_mass_in), nucleus_type(type_in) {}

  virtual ~Nucleus() = default;

  // Getters decided on no setters as the properties are fixed for a nucleus
  int get_atomic_number() const {return atomic_number;}
  int get_atomic_mass()   const {return atomic_mass;}
  std::string get_type()  const {return nucleus_type;}

  virtual void decay()=0;
  virtual void print_data()const=0;
};
