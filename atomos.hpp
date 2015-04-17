#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

#include "pipe.hpp"


/*
The responsibilities are shared like this:
You (the user of Atomos) are responsible for creating and storing Volumes and Pipes.
Volumes and Pipes are equivalent to nodes and edges on a graph.
Pipe destructors must be called before Volume destructors.
A Pipe connects two pipe fittings which are each connected to a volume.
To get a pipe fitting, look at the interface for the type of volume that you want to connect.


Atomos is responsible for the logic that ties the graph of volumes together
Atomos is respondible for storing and deleting Pipe fittings
and the flow of molecules between volumes any time tick() is called.
*/
class Atomos {
public:
    // this is a singleton
    static Atomos& getInstance() {
        // Guaranteed to be destroyed. Instantiated on first use.
        static Atomos instance;
        return instance;
    }

    // does one step for all connections between volumes
    void tick();

    // a counter of how often tick() has been called
    unsigned getCurrentTick() { return currentTick; }

    std::unordered_set<Pipe *> allPipes;  // only pipes should be able to add themselves
    // friend Pipe;  // pipes add themselves to this list
private:

    Atomos();

    // forbid copying
    Atomos(Atomos const&);
    void operator=(Atomos const&);

    unsigned currentTick;

};
