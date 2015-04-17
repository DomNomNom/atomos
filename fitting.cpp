#include "fitting.hpp"

#include <stdio.h>
#include <assert.h>

Fitting::~Fitting() {
    printf("~Fitting\n");
    // all pipes must be disconnected (destroyed) before a volume and its fittings are destroyed
    assert (pipe == nullptr);
}

Molecule_ptr& Fitting::getSlotToSwap() {
    return volume->getSlot(index);
}
