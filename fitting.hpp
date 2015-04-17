#pragma once

#include <memory>
#include "volumes/volume.hpp"
#include "molecule.hpp"
// #include "pipe.hpp"

class Pipe;

class Fitting {
public:
    Fitting(Volume *volume_) : pipe(nullptr), volume(volume_){}
    ~Fitting();
    Fitting(const Fitting& f) :pipe(f.pipe), volume(f.volume){}
    Fitting& operator=(const Fitting& f){
        this->pipe = f.pipe;
        this->volume = f.volume;
        return *this;
    }

    virtual Molecule_ptr& getSlotToSwap();


    unsigned index;  // set and used by the volume we are attached to
    Pipe *pipe;
private:

    Volume *volume;

    // friend Pipe;
};
