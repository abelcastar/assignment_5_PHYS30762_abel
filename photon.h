#pragma once
#include "Particle.h"
#include <iostream>
#include <vector>
#include <memory>

// Forward declaration of Electron
class Electron;

class Photon : public Particle {
private:
    std::vector<std::shared_ptr<Electron>> generated_electrons;

public:
    // Constructor
    Photon(double e) : Particle(e) {}

    // Add a pre-created electron
    void add_generated_electron(std::shared_ptr<Electron> electron) {
        generated_electrons.emplace_back(std::move(electron));
    }

    // Getter
    const std::vector<std::shared_ptr<Electron>>& get_generated_electrons() const {
        return generated_electrons;
    }

    // Override print_data
    void print_data() const override {
        std::cout << "A photon with energy " << get_energy() << " keV was emitted\n";
        std::cout << "Electrons generated: " << generated_electrons.size() << "\n" << std::endl;
    }

    // Friend functions
    friend double photoelectric_effect(const Photon& p);
    friend double compton_effect(Photon& p, double angle_deg);
    friend std::pair<std::shared_ptr<Electron>, std::shared_ptr<Electron>> pair_production(const Photon& p);
    std::pair<std::shared_ptr<Electron>, std::shared_ptr<Electron>> pair_production() const;

};
