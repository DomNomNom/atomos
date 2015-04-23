
#include "environment.hpp"
#include "../atomos.hpp"

#include <cstdlib>  // rand()
#include <stdio.h>
#include <assert.h>


Environment::Environment(int capacity) : molecules(capacity) {
    sliceRngResult = rand();
}


Environment::~Environment() {
    assert (connections.empty());  // all pipes must be destroyed prior to our deletion
}



// this should be called any time the fittings vector is modified
void Environment::recalculateConnectionIndecies() {
    // ensure that each fitting has a unique index in the range
    // 0 .. fittings.size()-1
    for (unsigned i=0; i<connections.size(); ++i) {
        ConnectionInfo *info = connections.at(i);
        assert (info->volume == this);
        info->connectionIndex = i;
    }
}


Molecule_ptr& Environment::getSlot(unsigned connectionIndex) {

    /*
    there are as many slices as fittings.
    each slice is the same size with the exception that the slice at the end may be larger

    example with 3 fittings and a capacity of 8,
    the molecules vector would be sliced up into 3 slices like this:
    == == ====

    we then
        pick a random slice such that no two fittings use the same slice
        return a random element within that slice
    */

    unsigned currentTick = Atomos::getInstance().getCurrentTick();
    if (lastRngTick != currentTick) {
        sliceRngResult = std::rand();  // done once per environment per tick
        lastRngTick = currentTick;
    }

    unsigned slice = (
        connectionIndex +
        sliceRngResult
        // + std::rand()
    ) % connections.size();

    // regular slice size
    unsigned sliceSize = molecules.size() / connections.size();  // note: integer division

    unsigned sliceOffset = slice * sliceSize; // beginning index of this slice

    // make last one longer
    // note that now sliceSize represents only the size of this slice
    // rather than what has been used for the sliceOffset
    if (slice == connections.size() - 1) {
        sliceSize += molecules.size() % connections.size();
    }

    unsigned sliceElement = std::rand() % sliceSize; // which index withinin the slice

    return molecules.at(sliceOffset + sliceElement);
}

ConnectionInfo* Environment::getConnectionInfo(unsigned connectionIndex) {
    ConnectionInfo *out = connections.at(connectionIndex);
    assert (out->volume == this);
    return out;
}

void Environment::takeControlOf(ConnectionInfo *info) {
    info->volume = this;
    info->connectionIndex = connections.size();
    connections.push_back(info);

    // we can't slice molucules into more slices than its size. Pidgin hole principle
    assert (connections.size() <= molecules.size());

    recalculateConnectionIndecies();
}

void Environment::release(unsigned connectionIndex) {

    ConnectionInfo *conn = connections.at(connectionIndex);
    assert (conn->connectionIndex == connectionIndex);
    assert (conn->volume == this);

    // safety: erase the pointer to this
    conn->volume = nullptr;

    // remove the connectionInfor from our list
    connections.erase(connections.begin() + connectionIndex);

    recalculateConnectionIndecies(); // updare indecies
}
