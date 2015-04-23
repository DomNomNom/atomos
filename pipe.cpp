#include "pipe.hpp"
#include "atomos.hpp"

#include "volumes/volume.hpp"

#include <assert.h>
#include <stdio.h>

Pipe::Pipe() {

    auto &allPipes = Atomos::getInstance().allPipes;
    assert (allPipes.find(this) == allPipes.end());  // we should not be in the set of allPipes
    allPipes.insert(this);
    assert (allPipes.find(this) != allPipes.end());  // we should be in the set of allPipes

    // // TODO: tell A and B to be attached to this
    // A->connect(this);
    // B->connect(this);

    // assert (A.volume != nullptr);
    // assert (B.volume != nullptr);
    A.volume = nullptr;
    B.volume = nullptr;

    // checkConnections();
}

Pipe::~Pipe() {
    checkConnections();

    auto &allPipes = Atomos::getInstance().allPipes;
    assert (allPipes.find(this) != allPipes.end());  // we should be in the set of allPipes
    allPipes.erase(this);

    A.volume->release(A.connectionIndex);
    B.volume->release(B.connectionIndex);

    // make sure the volumes have done their job
    assert (A.volume == nullptr);
    assert (B.volume == nullptr);
}


void Pipe::swapMolecules() {
    checkConnections();
    A.volume->getSlot(A.connectionIndex).swap(
        B.volume->getSlot(B.connectionIndex)
    );
}

void Pipe::checkConnections() {
    assert (A.volume != nullptr);
    assert (B.volume != nullptr);
    assert (A.volume->getConnectionInfo(A.connectionIndex) == &A);
    assert (B.volume->getConnectionInfo(B.connectionIndex) == &B);
}
