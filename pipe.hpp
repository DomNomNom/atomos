#pragma once

// #include "atomos.hpp"
#include "fitting.hpp"

// Allows molecules to pass from one Fitting to another
class Pipe {
public:
    const Fitting& A;
    const Fitting& B;

    Pipe(Fitting &a, Fitting &b);
    ~Pipe();

    void swapMolecules(); // should only be called by atomos

private:
    void checkFittings();  // checks whether our fittings to point to us
};

