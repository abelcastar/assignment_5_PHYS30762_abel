#include <iostream>
#include "stable.h"
#include "radioactive.h"
#include "photon.h"
#include "electron.h"
#include "particle.h"
#include "nucleus.h"




int main() {

RadioactiveNucleus na(11, 22, "Na", 2.603);
RadioactiveNucleus na22(11, 22, "Na", 2.603);

na.decay();

compton_effect(na, 1, 120.0);  // Scattering one of the 511 keV photons


Electron e2 = photoelectric_effect(na, 1);  // Clean and simple


compton_effect(na, 1, 120.0);  // Scattering one of the 511 keV photons

na22.decay();

auto electrons = pair_production(na22, 0);


pair_production(na22, 2);

Electron e3 = photoelectric_effect(na, 1); 

Electron e(300.0);

// Try to radiate 2 photons of 100 keV
e.radiate(2, 100.0);

e.print_data();
//adds to that vector
e.radiate(2,25.0);

// Print returned photons
for (const auto& p : e.get_emitted_photons()) {
    p->print_data();
}



    return 0;
}
