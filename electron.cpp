#include "electron.h"
#include "photon.h"
#include <iostream>

// Radiate a photon and store a copy internally
std::unique_ptr<Photon> Electron::radiate() {
    auto photon = std::make_unique<Photon>(100.0); // Placeholder energy value

    std::cout << "Electron radiated a photon:\n";
    photon->print_data();

    // Store a copy of the photon internally
    emitted_photons.emplace_back(std::make_unique<Photon>(*photon));

    return photon;
}