#include "photon.h"
#include "electron.h"
#include <cmath>

#include "Photon.h"
#include <cmath>

double photoelectric_effect(const Photon& p) {
    return p.get_energy(); // full energy absorbed
}

double compton_effect(Photon& p, double angle_deg) {
    double lost = angle_deg * 0.1; // simplified placeholder
    double updated = std::max(0.0, p.get_energy() - lost);
    p.set_energy(updated);
    return updated;
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
    return result;
}
