#include <iostream>
#include "stable.h"
#include "radioactive.h"


int main() {
    StableNucleus stable_nucleus(12, 24, "Magnesium"); 
    stable_nucleus.print_data();


    stable_nucleus.decay(); 

    RadioactiveNucleus rn1(27, 60, "Co", 5.272);
    RadioactiveNucleus rn2(55, 137, "Cs", 30.17);
    RadioactiveNucleus rn3(11, 22, "Na", 2.603);


    rn1.print_data();
    rn1.decay();
    rn1.print_data();
    rn1.pair_production();
    rn1.radiate();

    rn2.print_data();
    rn2.decay();
    rn2.print_data();
    rn2.pair_production();
    rn2.radiate();

    rn3.print_data();
    rn3.decay();
    rn3.print_data();
    rn3.decay();
    rn3.pair_production();
    rn3.radiate();






    return 0;
}
