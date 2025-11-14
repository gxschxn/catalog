#include "wheel.hpp"

Wheel::Wheel(int id, string name, double price, double diameter, string boltPattern)
    : AutoPart(id, name, price), diameter(diameter), boltPattern(boltPattern) {}

bool Wheel::isCompatibleWith(const string& vehicle) const {
    return vehicle.find("sedan") != string::npos && diameter >= 16.0;
}

PartType Wheel::getType() const { return PartType::WHEEL; }

string Wheel::getSpecs() const { 
    return to_string((int)diameter) + " inch, " + boltPattern; 
}