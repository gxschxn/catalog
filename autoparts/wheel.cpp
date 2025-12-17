#include "wheel.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

Wheel::Wheel(std::string id, std::string brand, std::string name, double price, double diameter, std::string boltPattern)
    : AutoPart(id, brand, name, price), diameter(diameter), boltPattern(boltPattern) {
    addCompatibility("all types");
}

std::string Wheel::getType() const { 
    std::ostringstream oss;
    oss << "Wheel: " << std::fixed << std::setprecision(1) << diameter << " inches";
    return oss.str();
}

std::string Wheel::getSpecifications() const { 
    std::ostringstream oss;
    oss << "Diameter: " << std::fixed << std::setprecision(1) << diameter 
        << " inches | Bolt pattern: " << boltPattern;
    return oss.str();
}

bool Wheel::checkCompatibility(const std::string& vehicle) const {
    std::string vehicleLower = vehicle;
    std::transform(vehicleLower.begin(), vehicleLower.end(), vehicleLower.begin(), ::tolower);
    
    return (vehicleLower.find("sedan") != std::string::npos && diameter >= 16.0) ||
           (vehicleLower.find("suv") != std::string::npos && diameter >= 17.0) ||
           (vehicleLower.find("truck") != std::string::npos && diameter >= 18.0);
}

std::string Wheel::getSpecs() const { 
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << diameter << " inches, " << boltPattern;
    return oss.str();
}

bool Wheel::operator>(const Wheel& other) const {
    return diameter > other.diameter;
}

Wheel& Wheel::operator=(const Wheel& other) {
    if (this != &other) {
        AutoPart::operator=(other);
        diameter = other.diameter;
        boltPattern = other.boltPattern;
    }
    return *this;
}