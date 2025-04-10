// THIS IS A PLACEHOLDER SO THAT RADIOACTIVE.H CAN COMPILE

#pragma once
#include <iostream>

class Photon {
private:
    double energy;

public:
    Photon(double e) : energy(e) {}

    double get_energy() const { return energy; }

    void print_data() const {
        std::cout << "A photon with energy " << energy << " keV was emitted" << std::endl;
    }
};
