#pragma once

#include "molecule.hpp"

// a container for molecules
// a volume may have a fixed or varying amount of fittings
// volumes are allowed to modify their contents (eg. space eating all gasses)
class Volume {
public:
    virtual Molecule_ptr& getSlot(unsigned fittingIndex) = 0;  // should only be called from fitting
};

