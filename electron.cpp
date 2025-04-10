#include "electron.h"
#include "photon.h"
#include <iostream>

std::shared_ptr<Photon> radiate(Electron& e) {
    auto photon = std::make_shared<Photon>(100.0); // placeholder value
    e.add_emitted_photon(photon);
    return photon;
}

std::shared_ptr<Photon> Electron::radiate() {
    auto photon = std::make_shared<Photon>(100.0); // placeholder energy
    add_emitted_photon(photon);

    std::cout << "Electron radiated a photon:\n";
    photon->print_data();
    return photon;
}