#include "radioactive.h"
#include "electron.h"
#include "photon.h"

void RadioactiveNucleus::decay() {
    if (!has_decayed) {
        std::cout << get_type() << " nucleus is decaying..." << std::endl;

        if (get_type() == "Cs") {
            emitted_photons.emplace_back(std::make_unique<Photon>(661.0));
            emitted_photons.back()->print_data();
        } else if (get_type() == "Na") {
            emitted_photons.emplace_back(std::make_unique<Photon>(1274.5));
            emitted_photons.back()->print_data();
        } else if (get_type() == "Co") {
            emitted_photons.emplace_back(std::make_unique<Photon>(1173.0));
            emitted_photons.back()->print_data();
            emitted_photons.emplace_back(std::make_unique<Photon>(1333.0));
            emitted_photons.back()->print_data();
        }

        has_decayed = true;
    } else {
        std::cerr << get_type() << " has already decayed.\n" << std::endl;
    }
}

void RadioactiveNucleus::print_data() const {
    std::cout << "\nRadioactive Nucleus: " << get_type()
              << " (Z=" << get_atomic_number()
              << ", A=" << get_atomic_mass() << ")"
              << ", Half-life: " << half_life << " years"
              << ", Decayed: " << (has_decayed ? "Yes" : "No")
              << ", Photons emitted: " << emitted_photons.size()
              << "\n" << std::endl;
}
