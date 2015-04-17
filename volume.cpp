#include "volume.hpp"

unsigned Volume::nextVolumeID = 0;


Volume::Volume(int capacity)
:
    molecules(capacity)
    // id(nextVolumeID++)
{ }

Volume::~Volume() { }
