#include "electron.h"
#include "photon.h"
#include <iostream>

std::vector<std::unique_ptr<Photon>> Electron::radiate(int number_of_photons, double photon_energy_keV) {
    std::vector<std::unique_ptr<Photon>> emitted_now;

    double total_required_energy = number_of_photons * photon_energy_keV;
    double current_energy = get_energy();

    std::cout << "[Radiate] Request: "
              << number_of_photons << " photon(s) with "
              << photon_energy_keV << " keV each from electron with "
              << current_energy << " keV.\n";

    if (number_of_photons <= 0 || photon_energy_keV <= 0.0) {
        std::cerr << "[Error] Invalid input: number and energy must be positive.\n" << std::endl;
        return emitted_now;
    }

    if (total_required_energy > current_energy) {
        std::cerr << "[Radiate] Failed: Not enough energy to radiate "
                  << number_of_photons << " photon(s) at "
                  << photon_energy_keV << " keV each (Total: "
                  << total_required_energy << " keV, Available: "
                  << current_energy << " keV).\n" << std::endl;
        return emitted_now;
    }

    for (int i = 0; i < number_of_photons; ++i) {
        auto photon = std::make_unique<Photon>(photon_energy_keV);
        emitted_now.emplace_back(std::make_unique<Photon>(*photon));      // Copy for internal record
        emitted_photons.emplace_back(std::make_unique<Photon>(*photon));  // Store for tracking
    }

    set_energy(current_energy - total_required_energy);

    std::cout << "[Radiate] Successful: "
              << number_of_photons << " photon(s) emitted.\n"
              << "  Remaining electron energy: " << get_energy() << " keV\n" << std::endl;

    return emitted_now;
}

const std::vector<std::unique_ptr<Photon>>& Electron::get_emitted_photons() const {
    return emitted_photons;
}

void Electron::print_data() const {
    std::cout << "Electron:\n"
              << "  Kinetic Energy: " << get_energy() << " keV\n"
              << "  Rest Mass: " << rest_mass << " MeV\n"
              << "  Photons emitted: " << emitted_photons.size();

    if (!emitted_photons.empty()) {
        std::cout << " (Each with "
                  << emitted_photons.front()->get_energy()
                  << " keV)";
    }

    std::cout << "\n" << std::endl;
}
