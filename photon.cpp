#include "photon.h"
#include "electron.h"
#include <cmath>

double photoelectric_effect(const Photon& p) {
    return p.get_energy(); 
}

double compton_effect(Photon& p, double angle_deg) {
    double lost_energy = angle_deg * 0.1;
    double updated = std::max(0.0, p.get_energy() - lost_energy);
    p.set_energy(updated);  
    return updated;
}

std::pair<std::shared_ptr<Electron>, std::shared_ptr<Electron>> pair_production(const Photon& p) {
    double electron_energy = p.get_energy() / 2.0;
    auto e1 = std::make_shared<Electron>(electron_energy);
    auto e2 = std::make_shared<Electron>(electron_energy);
    return {e1, e2};
}

std::pair<std::shared_ptr<Electron>, std::shared_ptr<Electron>> Photon::pair_production() const {
    if (get_energy() < 2 * Electron::rest_mass * 1000) {
        std::cout << "Photon energy too low for pair production.\n" << std::endl;
        return {nullptr, nullptr};
    }

    double e_energy = get_energy() / 2.0;
    auto e1 = std::make_shared<Electron>(e_energy);
    auto e2 = std::make_shared<Electron>(e_energy);

    std::cout << "Pair production created two electrons from photon (" 
              << get_energy() << " keV):\n";
    e1->print_data();
    e2->print_data();

    return {e1, e2};
}
