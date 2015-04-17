#include "atomos.hpp"

#include <stdio.h>



Atomos::Atomos() : currentTick(0) { }


void Atomos::tick() {
    // printf("tick tock %d\n", getCurrentTick());
    currentTick += 1;

    // iterate over pipes and make them do swaps
    for (Pipe *p : allPipes) {
        p->swapMolecules();
    }
}
