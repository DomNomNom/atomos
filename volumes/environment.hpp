#pragma once

#include <vector>

#include "volume.hpp"
#include "../molecule.hpp"
#include "../fitting.hpp"


// has a finite capacity
// can have any amount of fittings
class Environment : Volume {
public:
    std::vector<Molecule_ptr> molecules;
    Environment(int capacity);
    ~Environment();


    const Fitting_ptr& getNewFitting();

    // the next two should only be called from fitting
    Molecule_ptr& getSlot(unsigned fittingIndex);
    void removeFitting(unsigned fittingIndex);


private:
    std::vector<Fitting_ptr> fittings;
    void recalculateFittingIndecies();
};
