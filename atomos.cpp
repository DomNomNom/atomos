#include "atomos.hpp"

#include <stdio.h>




// Volume_ptr Atomos::createVolume(int capacity) {
//     Volume_ptr out(new Volume(capacity));
//     volumes.insert(out);
//     return out;
// }


void Atomos::tick() {
    printf("tick tock %d\n", getCurrentTick());
    currentTick += 1;
}
