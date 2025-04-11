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


public:
    // Constructor
    RadioactiveNucleus(int z, int a, const std::string& type, double hl)
        : Nucleus(z, a, type), half_life(hl), has_decayed(false) {}

// --- Rule of 5 ---

    // Destructor
    ~RadioactiveNucleus() = default;

    // Copy constructor
    RadioactiveNucleus(const RadioactiveNucleus& other)
        : Nucleus(other.get_atomic_number(), other.get_atomic_mass(), other.get_type()),
          half_life(other.half_life),
          has_decayed(false)  // copying resets decay state
    {
        std::cout << "[Copy constructor called — photons not copied]\n";
    }

    // Copy assignment
    RadioactiveNucleus& operator=(const RadioactiveNucleus& other) {
        if (this != &other) {
            half_life = other.half_life;
            has_decayed = false;
            emitted_photons.clear();
            std::cout << "[Copy assignment called — photons not copied]\n";
        }
        return *this;
    }

    // Move constructor
    RadioactiveNucleus(RadioactiveNucleus&& other) noexcept = default;

    // Move assignment
    RadioactiveNucleus& operator=(RadioactiveNucleus&& other) noexcept = default;

    void decay() override;
    void print_data() const override;



    // Getters
    double get_half_life() const { return half_life; }
    bool is_decayed() const { return has_decayed; }

    const std::vector<std::shared_ptr<Photon>>& get_emitted_photons() const {
        return emitted_photons;
    }




};
