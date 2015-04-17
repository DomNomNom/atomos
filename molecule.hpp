#pragma once

#include <memory>


// one instance of this class represents
// one fixed quanity of a chemical molecule
class Molecule
{
public:
    Molecule(int type_) : type(type_){};
    ~Molecule(){};

    int type;
};


typedef std::unique_ptr<Molecule> Molecule_ptr;

