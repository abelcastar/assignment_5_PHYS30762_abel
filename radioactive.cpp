#include "radioactive.h"
#include "electron.h"
#include "photon.h"

void RadioactiveNucleus::pair_production() {
    if (!has_decayed || emitted_photons.empty()) {
        std::cout << get_type() << " has not decayed or has no photons to process.\n" << std::endl;
        return;
    }

    std::cout << "\nPerforming pair production on photons from " << get_type() << "...\n" << std::endl;

    for (const auto& photon : emitted_photons) {
        auto [e1, e2] = photon->pair_production();

        if (e1) produced_electrons.emplace_back(e1);
        if (e2) produced_electrons.emplace_back(e2);
    }
}

void RadioactiveNucleus::radiate() {
    if (produced_electrons.empty()) {
        std::cout << "No electrons available for radiation from " << get_type() << ".\n" << std::endl;
        return;
    }

    std::cout << "\nRadiating photons from electrons produced by " << get_type() << "...\n" << std::endl;

    for (const auto& electron : produced_electrons) {
        electron->radiate(); // handles its own printing and photon tracking
    }
}
