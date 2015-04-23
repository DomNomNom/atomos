#pragma once

#include "../molecule.hpp"
#include "../pipe.hpp"

// a container for molecules
// a volume may have a fixed or varying amount of fittings
// volumes are allowed to modify their contents (eg. space eating all gasses)
class Volume {
public:
    virtual ~Volume(){};

    // the next ones should only be called from Fitting
    virtual Molecule_ptr& getSlot(unsigned connectionIndex) = 0;
    virtual ConnectionInfo* getConnectionInfo(unsigned connectionIndex) = 0;
    virtual void release(unsigned connectionIndex) = 0;

};

