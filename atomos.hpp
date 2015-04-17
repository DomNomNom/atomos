#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

#include "pipe.hpp"
// #include "volume.hpp"


/*
The responsibilities are shared like this:
You (the user of Atomos) are responsible for creating and storing Volumes and Pipes.
Volumes and Pipes are equivalent to nodes and edges on a graph.
Pipe destructors must be called before Volume destructors.


Atomos is responsible for the logic that ties the graph of volumes together
and the flow of molecules between volumes any time tick() is called.
*/
class Atomos {
public:
    // this is a singleton
    static Atomos& getInstance()
    {
        static Atomos instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

    // does one step for all connections between volumes
    void tick();

    // a counter of how often tick() has been called
    unsigned getCurrentTick() { return currentTick; }

private:
    // std::unordered_set<Volume_ptr> volumes;

    Atomos(){};
    ~Atomos(){};

    // forbid copying
    Atomos(Atomos const&)          = delete;
    void operator=(Atomos const&)  = delete;

    unsigned currentTick = 0;

    std::unordered_set<Pipe*> allPipes;
    friend Pipe;  // borders add themselves to this list
};
