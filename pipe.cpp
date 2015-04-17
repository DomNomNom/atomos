#include "pipe.hpp"
#include "atomos.hpp"

#include <assert.h>
#include <stdio.h>

Pipe::Pipe(const Fitting_ptr &a, const Fitting_ptr &b) : A(a), B(b) {
    auto &allPipes = Atomos::getInstance().allPipes;
    assert (allPipes.find(this) == allPipes.end());  // we should not be in the set of allPipes
    allPipes.insert(this);
    assert (allPipes.find(this) != allPipes.end());  // we should be in the set of allPipes

    // TODO: tell A and B to be attached to this
    A->connect(this);
    B->connect(this);

    checkFittings();
}

Pipe::~Pipe() {
    checkFittings();

    auto &allPipes = Atomos::getInstance().allPipes;
    assert (allPipes.find(this) != allPipes.end());  // we should be in the set of allPipes
    allPipes.erase(this);

    A->disconnect();
    B->disconnect();
}


void Pipe::swapMolecules() {
    checkFittings();
    // TODO
}

void Pipe::checkFittings() {
    assert (A->getPipe() == this);
    assert (B->getPipe() == this);
}
