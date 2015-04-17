#pragma once

// #include "atomos.hpp"
#include "fitting.hpp"

// Allows molecules to pass from one Fitting to another
class Pipe {
public:
    std::shared_ptr<Fitting> A;
    std::shared_ptr<Fitting> B;

    Pipe(const Fitting_ptr &a, const Fitting_ptr &b);
    ~Pipe();

    void swapMolecules(); // should only be called by atomos

private:
    void checkFittings();  // checks whether our fittings to point to us
};
