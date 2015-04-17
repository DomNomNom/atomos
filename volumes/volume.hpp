#pragma once

#include "../molecule.hpp"

// a container for molecules
// a volume may have a fixed or varying amount of fittings
// volumes are allowed to modify their contents (eg. space eating all gasses)
class Volume {
public:
    virtual ~Volume(){};

    // the next ones should only be called from Fitting
    virtual Molecule_ptr& getSlot(unsigned fittingIndex) = 0;
    virtual void removeFitting(unsigned fittingIndex) = 0;
};

