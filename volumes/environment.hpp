#pragma once

#include <vector>

#include "volume.hpp"
#include "../molecule.hpp"
#include "../pipe.hpp"


// has a finite capacity
// can have any amount of fittings
class Environment : Volume {
public:
    std::vector<Molecule_ptr> molecules;
    Environment(int capacity);
    ~Environment();



    // the next two should only be called from fitting
    Molecule_ptr& getSlot(unsigned connectionIndex);
    // void addConnection(ConnectionInfo *info);

    virtual ConnectionInfo* getConnectionInfo(unsigned connectionIndex);


    // should only be called by Pipe TODO: enforce this
    void takeControlOf(ConnectionInfo *info);
    virtual void release(unsigned connectionIndex);

private:
    std::vector<ConnectionInfo *> connections;  // note: we can't get the pipe from this
    void recalculateConnectionIndecies();

    // a random number shared by all fittings. updated each tick.
    unsigned sliceRngResult = 0;
    unsigned lastRngTick = 0;
    unsigned getSliceRngResult();
};
