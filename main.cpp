#include <iostream>
#include "stable.h"
#include "radioactive.h"
#include "photon.h"
#include "electron.h"
#include "particle.h"
#include "nucleus.h"




int main() {
    StableNucleus stable_nucleus(12, 24, "Magnesium"); 
    stable_nucleus.print_data();


    stable_nucleus.decay(); 

    RadioactiveNucleus rn(55, 137, "Cs", 30.17);
    rn.print_data();
    rn.decay();
    rn.print_data();

    // Attempt pair production on each emitted photon
    const auto& photons = rn.get_emitted_photons();

    for (const auto& photon : photons) {
        std::cout << "\n--- Testing pair production ---\n";
        photon->print_data();

        auto electrons = pair_production(*photon);

        if (electrons.empty()) {
            std::cout << "→ No electrons were created.\n";
        } else {
            std::cout << "Successfully created " << electrons.size() << " electrons.\n";
        }

        std::cout << "-------------------------------\n";
    }






    return 0;
}
