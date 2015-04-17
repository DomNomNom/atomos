#pragma once

#include <memory>
#include <stdio.h>

#include "volumes/volume.hpp"
#include "molecule.hpp"
// #include "pipe.hpp"

class Pipe;

class Fitting {
public:
    Fitting(Volume *volume_) : pipe(nullptr), volume(volume_){}
    ~Fitting();

    virtual Molecule_ptr& getSlotToSwap();


    unsigned index;  // set and used by the volume we are attached to

    Pipe* getPipe() { return pipe; }

    // these next two should only be called by Pipe
    // friend Pipe;
    void connect(Pipe *p) { pipe = p; }
    void disconnect() {
        pipe = nullptr;

        // notify our volume that we are disconnected
        volume->removeFitting(index); //
        printf("fitting disconnected\n");
    }

private:
    Pipe *pipe;

    Volume *volume;
};


typedef std::shared_ptr<Fitting> Fitting_ptr;
