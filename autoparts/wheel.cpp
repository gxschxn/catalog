#include "wheel.hpp"

Wheel::Wheel(string id, string name, double price, double diameter, string boltPattern)
    : AutoPart(id, name, price), diameter(diameter), boltPattern(boltPattern) {}

bool Wheel::isCompatibleWith(const string& vehicle) const {
    return vehicle.find("sedan") != string::npos && diameter >= 16.0;
}

string Wheel::getType() const { return "Wheel"; }

string Wheel::getSpecs() const { 
    return to_string((int)diameter) + " inch, " + boltPattern; 
}