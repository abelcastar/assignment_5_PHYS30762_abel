#include <iostream>
#include "stable.h"
#include "radioactive.h"


int main() {
    StableNucleus stable_nucleus(12, 24, "Magnesium"); 
    stable_nucleus.print_data();


    stable_nucleus.decay(); 

    RadioactiveNucleus rn(55, 137, "Cs", 30.17); // Half-life = 30.17 years

    // Print initial state
    rn.print_data();

    // Trigger decay
    rn.decay();

    // Print post-decay state
    rn.print_data();





    return 0;
}
