#include "wheel.hpp"
#include <algorithm>
#include <iostream>

Wheel::Wheel(std::string id, std::string name, double price, double diameter, std::string boltPattern)
    : AutoPart(id, name, price), diameter(diameter), boltPattern(boltPattern) {
    addCompatibility("all types");
}

bool Wheel::isCompatibleWith(const std::string& vehicle) const {
    std::string vehicleLower = vehicle;
    std::transform(vehicleLower.begin(), vehicleLower.end(), vehicleLower.begin(), ::tolower);
    
    return (vehicleLower.find("sedan") != std::string::npos && diameter >= 16.0) ||
           (vehicleLower.find("suv") != std::string::npos && diameter >= 17.0);
}

std::string Wheel::getType() const { 
    return "Wheel: " + std::to_string(static_cast<int>(diameter)) + " inches"; 
}

AutoPart* Wheel::clone() const {
    Wheel* newWheel = new Wheel(id, name, price, diameter, boltPattern);
    newWheel->setQuantity(quantity);
    return newWheel;
}

CloneablePart* Wheel::deepClone() const {
    return this->clone();
}

CloneablePart* Wheel::shallowClone() const {
    return this->clone();
}

std::string Wheel::getSpecs() const { 
    return std::to_string(static_cast<int>(diameter)) + " inches, " + boltPattern; 
}

std::string Wheel::getSpecialInfo() const {
    return "Wheel specs: " + getSpecs();
}

std::string Wheel::getSpecialInfoVirtual() const {
    return "Virtual wheel specs: " + getSpecs();
}

Wheel* Wheel::operator+(const Wheel& other) const {
    std::string newId = id + "_" + other.id;
    std::string newName = name + " & " + other.name + " set";
    double newPrice = price + other.price;
    double avgDiameter = (diameter + other.diameter) / 2;
    std::string newBoltPattern = boltPattern + "/" + other.boltPattern;
    
    return new Wheel(newId, newName, newPrice, avgDiameter, newBoltPattern);
}

bool Wheel::operator>(const Wheel& other) const {
    return diameter > other.diameter;
}