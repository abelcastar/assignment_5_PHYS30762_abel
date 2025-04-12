#pragma once
#include "particle.h"
#include "electron.h"
#include "nucleus.h"
#include <iostream>
#include <vector>
#include <memory>
#include <utility>

class Photon : public Particle {
public:
    Photon(double e) : Particle(e) {}

    void print_data() const override {
        std::cout << "Photon with energy " << get_energy() << " keV was emitted.\n" << std::endl;
    }

    // Friend functions (interactions)
    friend Electron photoelectric_effect(const Photon& p); 
    friend void compton_effect(Photon& p, double angle_deg);
    friend std::vector<std::unique_ptr<Electron>> pair_production(const Photon& p);


};

Electron photoelectric_effect(const Nucleus& nucleus, size_t photon_index);
void compton_effect(const Nucleus& nucleus, size_t photon_index, double angle_deg);
std::vector<std::unique_ptr<Electron>> pair_production(const Nucleus& nucleus, size_t photon_index);

