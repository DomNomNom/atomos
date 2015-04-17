#pragma once

#include <memory>
#include "volumes/volume.hpp"
#include "molecule.hpp"
// #include "pipe.hpp"

class Pipe;

class Fitting {
public:
    Fitting(Volume &volume_) : volume(volume_), pipe(nullptr) {};
    ~Fitting();

    virtual Molecule_ptr& getSlotToSwap();


    unsigned index;  // set and used by the volume we are attached to
private:

    Volume &volume;

    friend Pipe;
    Pipe *pipe;
};
