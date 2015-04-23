#pragma once

// #include "atomos.hpp"
// #include "fitting.hpp"
// #include

class Volume; // forward declaration


// stored within a pipe
typedef struct {
    unsigned connectionIndex;  // Volume may change this
    Volume *volume;
} ConnectionInfo;


// Allows molecules to pass from one Fitting to another
class Pipe {
public:
    ConnectionInfo A;
    ConnectionInfo B;

    Pipe();
    ~Pipe();

    void swapMolecules(); // should only be called by atomos

    // checks whether our fittings are connectec andto point to us
    void checkConnections();
private:
};


