#include <vector>

#include "volume.hpp"
#include "../molecule.hpp"


// has a finite capacity
// can have any amount of fittings
class Environment : Volume {
public:
    std::vector<Molecule_ptr> molecules;
    Environment(int capacity);


    Fitting& getNewFitting();

    virtual Molecule_ptr& getSlot(unsigned fittingIndex);  // should only be called from fitting

private:
    std::vector<Fitting> fittings;
    void recalculateFittingIndecies();
};
