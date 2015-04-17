#pragma once

#include <vector>
#include <memory>
#include <unordered_set>


#include "molecule.hpp"
// #include "border.hpp"

class Border;


// a container for molecules
// subclasses of volume are allowed to modify their contents (eg. space eating all gasses)
class Volume
{
public:
    std::vector<std::unique_ptr<Molecule>> molecules;

    Volume(int capacity);
    ~Volume();

    unsigned capacity() { return molecules.size(); }

private:
    friend Border;
    std::unordered_set<Border*> borders;

    static unsigned nextVolumeID;

};


// const unsigned id;
// bool operator==(const Volume &other) const {
//     return other.id == id;
// }

// // teach std:: how to compute the hash for a volume (it just hashes the volumes id)
// // this way we can
// namespace std {
//   template <>
//   struct hash<Volume> {
//     std::size_t operator()(const Volume& k) const {
//       // using std::size_t;
//       // using std::hash;
//       // using std::string;

//       // Compute individual hash values for first,
//       // second and third and combine them using XOR
//       // and bit shifting:

//       return std::hash<int>()(k.id);
//     }
//   };
// }
