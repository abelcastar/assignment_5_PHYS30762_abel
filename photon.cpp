#include "photon.h"
#include "electron.h"
#include "radioactive.h"
#include <cmath>
#include <iostream>

static Photon* validate_interaction(const Nucleus& nucleus, size_t i, const std::string& context) {
    const auto* radioactive_ptr = dynamic_cast<const RadioactiveNucleus*>(&nucleus);
    if (!radioactive_ptr) {
        std::cerr << "[Warning] " << context << ": interaction only valid on radioactive nuclei.\n";
        return nullptr;
    }

    if (!radioactive_ptr->is_decayed()) {
        std::cerr << "[Warning] " << context << ": nucleus has not decayed yet.\n";
        return nullptr;
    }

    const auto& photons = radioactive_ptr->get_emitted_photons();
    if (i >= photons.size()) {
        std::cerr << "[Warning] " << context << ": invalid photon index " << i
                  << ". Only " << photons.size() << " photons available.\n";
        return nullptr;
    }

    Photon* photon = photons[i].get();
    if (photon->get_energy() <= 0.0) {
        std::cerr << "[Warning] " << context << ": cannot interact with photon of 0 keV (interaction skipped).\n";
        return nullptr;
    }

    return photon;
}



Electron photoelectric_effect(const Photon& p) {
    std::cout << "[Photoelectric Effect called]\n";
    std::cout << "  Photon with energy " << p.get_energy() << " keV fully absorbed (energy set to 0 keV).\n";
    std::cout << "  One electron emitted with: " << p.get_energy() << "keV (Note: Work function ignored since highest possible ~ 6eV)\n";
    const_cast<Photon&>(p).set_energy(0.0);  // Mark as "absorved"



    return Electron(p.get_energy());
}

void compton_effect(Photon& p, double angle_deg) {

    double angle_rad = angle_deg * Electron::PI / 180.0;
    double initial_energy = p.get_energy();
    double rest_mass_keV = Electron::rest_mass * 1000.0;

    double scattered_energy = initial_energy / (1 + (initial_energy / rest_mass_keV) * (1 - std::cos(angle_rad)));
    p.set_energy(scattered_energy);

    std::cout << "[Compton Scattering called]\n";
    std::cout << "  Incoming photon energy: " << initial_energy << " keV\n";
    std::cout << "  Scattering angle: " << angle_deg << " degrees\n";
    std::cout << "  Photon energy after scattering: " << scattered_energy << " keV\n\n";
}

std::vector<std::unique_ptr<Electron>> pair_production(const Photon& p) {
    constexpr double rest_mass_keV = Electron::rest_mass * 1000;

    if (p.get_energy() < 2 * rest_mass_keV) {
        std::cout << "Pair production failed: photon energy ("
                  << p.get_energy() << " keV) is too low.\n"
                  << "Requires at least " << 2 * rest_mass_keV << " keV.\n" << std::endl;
        return {};
    }

    double energy_per_electron = p.get_energy() / 2.0;
    auto e1 = std::make_unique<Electron>(energy_per_electron);
    auto e2 = std::make_unique<Electron>(energy_per_electron);

    std::cout << "Pair production successful from photon (" << p.get_energy() << " keV):\n";
    e1->print_data();
    e2->print_data();

    std::vector<std::unique_ptr<Electron>> result;
    result.push_back(std::move(e1));
    result.push_back(std::move(e2));
    const_cast<Photon&>(p).set_energy(0.0);  // Mark as "absorved"

    return result;
}

Electron photoelectric_effect(const Nucleus& nucleus, size_t i) {
    Photon* photon = validate_interaction(nucleus, i, "Photoelectric Effect");
    if (!photon) {
        std::cerr << "[Follow Up Warning] Dummy Electron created (0 keV) the interaction was skipped.\n";
        return Electron(0.0);
    }

    return photoelectric_effect(*photon);
}



void compton_effect(const Nucleus& nucleus, size_t i, double angle_deg) {
    Photon* photon = validate_interaction(nucleus, i, "Compton Scattering");
    if (!photon) return;

    compton_effect(*photon, angle_deg);
}

std::vector<std::unique_ptr<Electron>> pair_production(const Nucleus& nucleus, size_t i) {
    Photon* photon = validate_interaction(nucleus, i, "Pair Production");
    if (!photon) return {};

    return pair_production(*photon);
}

