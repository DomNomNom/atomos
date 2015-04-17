
#include "environment.hpp"
#include "../atomos.hpp"

#include <cstdlib>  // rand()

Environment::Environment(int capacity) : molecules(capacity) { }

const Fitting& Environment::getNewFitting() {
    fittings.push_back(Fitting(*this));
    recalculateFittingIndecies();
    return fittings.back();
}

// this should be called any time the fittings vector is modified
void Environment::recalculateFittingIndecies() {
    // ensure that each fitting has a unique index in the range
    // 0 .. fittings.size()-1
    for (unsigned i=0; i<fittings.size(); ++i) {
        fittings.at(i).index = i;
    }
}

Molecule_ptr& Environment::getSlot(unsigned fittingIndex) {

    /*
    there are as many slices as fittings.
    each slice is the same size with the exception that the slice at the end may be larger

    example with 3 fittings and a capacity of 8,
    the molecules vector would be sliced up into 3 slices like this:
    == == ====

    we then
        pick a slice determined by fittingIndex and rotated each atmos tick
        return a random element within that slice
    */

    unsigned slice = (
        fittingIndex +
        Atomos::getInstance().getCurrentTick()  // this makes it cycle over time
    ) % fittings.size();

    // regular slice size
    unsigned sliceSize = molecules.size() / fittings.size();  // note: integer division

    unsigned sliceOffset = fittingIndex * sliceSize; // beginning index of this slice

    // make last one longer
    // note that now sliceSize represents only the size of this slice
    // rather than what has been used for the sliceOffset
    if (slice == fittings.size() - 1) {
        sliceSize += molecules.size() % fittings.size();
    }

    unsigned sliceElement = std::rand() % sliceSize; // which index withinin the slice

    return molecules.at(sliceOffset + sliceElement);
}
