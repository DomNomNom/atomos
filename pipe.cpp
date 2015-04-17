#include "pipe.hpp"
#include "atomos.hpp"

#include <assert.h>

Pipe::Pipe(Fitting &a, Fitting &b) : A(a), B(b) {
    auto allPipes = Atomos::getInstance().allPipes;
    assert (allPipes.find(this) == allPipes.end());  // we should not be in the set of allPipes
    allPipes.insert(this);

    // TODO: tell A and B to be attached to this
    A.pipe = this;
    A.pipe = this;
}

Pipe::~Pipe() {
    checkFittings();

    auto allPipes = Atomos::getInstance().allPipes;
    assert (allPipes.find(this) != allPipes.end());  // we should be in the set of allPipes
    allPipes.erase(this);

    A.pipe = nullptr;
    B.pipe = nullptr;
}


void Pipe::swapMolecules() {
    checkFittings();
    // TODO
}

void Pipe::checkFittings() {
    assert (A.pipe == this);
    assert (B.pipe == this);
}
