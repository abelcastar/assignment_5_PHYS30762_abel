// This file implements the decay logic for RadioactiveNucleus. It simulates 
// gamma emission for Cs, Na, and Co isotopes. Na positron annihilation is 
// simplified to direct 511 keV photon emission due to short lifetime of the
// positron. A lambda ensures DRY logic. Default constructor omitted because
// the user should initialise objects with all the correct information.
//=====================================================================

#include "radioactive.h"
#include "photon.h"

RadioactiveNucleus::RadioactiveNucleus(int atomic_number_in, int atomic_mass_in, const std::string& type_in, double half_life_in)
    : Nucleus(atomic_number_in, atomic_mass_in, type_in),half_life(half_life_in),has_decayed(false) {}

// Destructor
RadioactiveNucleus::~RadioactiveNucleus() = default;

// Copy Constructor
RadioactiveNucleus::RadioactiveNucleus(const RadioactiveNucleus& other)
    : Nucleus(other.get_atomic_number(), other.get_atomic_mass(), other.get_type()),half_life(other.half_life),has_decayed(false)
    {std::cout << "[Copy constructor called — photons not copied]\n"<<std::endl;}

// Copy Assignment
RadioactiveNucleus& RadioactiveNucleus::operator=(const RadioactiveNucleus& other)
{
  if(this != &other) {half_life = other.half_life; has_decayed = false; emitted_photons.clear();
    std::cout << "[Copy assignment called — photons not copied]\n"<<std::endl;}
  return *this;
}

// Move Constructor
RadioactiveNucleus::RadioactiveNucleus(RadioactiveNucleus&& other) noexcept = default;

// Move Assignment
RadioactiveNucleus& RadioactiveNucleus::operator=(RadioactiveNucleus&& other) noexcept = default;


void RadioactiveNucleus::decay() {
  if(!has_decayed)
  { 
    std::cout<<get_type()<<" nucleus is decaying..."<<std::endl;

    // Lambda function to emit and immediately print photon data
    auto emit_photon = [&](double energy)
    {
    emitted_photons.emplace_back(std::make_unique<Photon>(energy));
    emitted_photons.back()->print_data();
    };

    if(get_type() == "Cs"){emit_photon(661.0);}

    else if(get_type() == "Na") {emit_photon(1274.5);

    std::cout<<"A positron was emitted and annihilated with an electron.\n"<<
    "Two 511 keV photons were produced from annihilation.\n"<<std::endl;

    emit_photon(511.0); emit_photon(511.0);}

    else if(get_type() == "Co") {emit_photon(1173.0); emit_photon(1333.0);}
  
    has_decayed = true;
  }
  
  else{std::cerr<<get_type()<<" has already decayed.\n"<<std::endl;}
}

void RadioactiveNucleus::print_data() const
{
  std::cout<<"\nRadioactive Nucleus: "<<get_type()<<" (Z="<<get_atomic_number()
       <<", A="<<get_atomic_mass()<<")"<<", Half-life: "<<half_life<<" years"
       <<", Decayed: "<<(has_decayed ? "Yes" : "No")<<", Photons emitted: "
       <<emitted_photons.size()<<"\n"<<std::endl;
}
