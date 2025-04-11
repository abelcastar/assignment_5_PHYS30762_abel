#pragma once
#include "particle.h"
#include "electron.h" 
#include <iostream>
#include <vector>
#include <memory>

class Photon : public Particle {
public:
    Photon(double e) : Particle(e) {}

    void print_data() const override {
        std::cout << "Photon with energy " << get_energy() << " keV\n" << std::endl;
    }

    // Friend functions (interactions)
    friend double photoelectric_effect(const Photon& p);
    friend double compton_effect(Photon& p, double angle_deg);
    friend std::vector<std::unique_ptr<Electron>> pair_production(const Photon& p);
};
