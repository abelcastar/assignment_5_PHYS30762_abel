#include <iostream>
#include "stable.h"

int main() {
    StableNucleus stable_nucleus(12, 24, "Magnesium"); 
    stable_nucleus.print_data();


    stable_nucleus.decay(); 


    return 0;
}
