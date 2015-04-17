#include "atomos.hpp"

#include <stdio.h>



Atomos::Atomos() : currentTick(0) { }


void Atomos::tick() {
    // printf("tick tock %d\n", getCurrentTick());
    currentTick += 1;

    // TODO: iterate over pipes
}
