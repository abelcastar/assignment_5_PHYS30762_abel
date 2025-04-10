#pragma once
#include "nucleus.h"
#include "photon.h"
#include "electron.h"

#include <iostream>
#include <memory>
#include <vector>

class RadioactiveNucleus : public Nucleus {
private:
    double half_life;
    bool has_decayed;
    std::vector<std::shared_ptr<Photon>> emitted_photons;
    std::vector<std::shared_ptr<Electron>> produced_electrons;


public:
    // Constructor
    RadioactiveNucleus(int z, int a, const std::string& type, double hl)
        : Nucleus(z, a, type), half_life(hl), has_decayed(false) {}

    // Decay function gtta think about if shared is best????
void decay() override {
    if (!has_decayed) {
        std::cout << get_type() << " nucleus is decaying..." << std::endl;

        if (get_type() == "Cs") {
            emitted_photons.emplace_back(std::make_shared<Photon>(661.0));
            emitted_photons.back()->print_data();
        } else if (get_type() == "Na") {
            emitted_photons.emplace_back(std::make_shared<Photon>(1274.5)); // I have to have a look at the positron annihilation 511 peak
            emitted_photons.back()->print_data();
        } else if (get_type() == "Co") {
            emitted_photons.emplace_back(std::make_shared<Photon>(1173.0));
            emitted_photons.back()->print_data();
            emitted_photons.emplace_back(std::make_shared<Photon>(1333.0));
            emitted_photons.back()->print_data();
        }

        has_decayed = true;
    } else {
        std::cerr << get_type() << " has already decayed." << std::endl;
    }
}


    // Print all info
    void print_data() const override {
        std::cout << "\nRadioactive Nucleus: " << get_type()
                  << " (Z=" << get_atomic_number()
                  << ", A=" << get_atomic_mass() << ")"
                  << ", Half-life: " << half_life << " s"
                  << ", Decayed: " << (has_decayed ? "Yes" : "No")
                  << ", Photons emitted: " << emitted_photons.size()
                  << "\n" << std::endl;
    }

    // Getters
    double get_half_life() const { return half_life; }
    bool is_decayed() const { return has_decayed; }

    const std::vector<std::shared_ptr<Photon>>& get_emitted_photons() const {
        return emitted_photons;
    }

    const std::vector<std::shared_ptr<Electron>>& get_produced_electrons() const {
        return produced_electrons;
    }

    // functions needed for radiation
    void pair_production(); // self-contained
    void radiate();         // self-contained


};
