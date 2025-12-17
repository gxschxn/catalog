#include "enginepart.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

EnginePart::EnginePart(std::string id, std::string brand, std::string name, double price, std::string engineType)
    : AutoPart(id, brand, name, price), engineType(engineType) {
    initializeCompatibility();
    addCompatibility("universal");
}

EnginePart::~EnginePart() {
}

void EnginePart::initializeCompatibility() {
    if (engineType == "V6") {
        compatibleVehicles.push_back("toyota camry");
        compatibleVehicles.push_back("toyota rav4");
        compatibleVehicles.push_back("honda accord");
    } else if (engineType.find("EJ") != std::string::npos) {
        compatibleVehicles.push_back("subaru impreza");
        compatibleVehicles.push_back("subaru forester");
    } else if (engineType == "V12") {
        compatibleVehicles.push_back("ferrari 488");
        compatibleVehicles.push_back("lamborghini aventador");
    } else if (engineType == "L4") {
        compatibleVehicles.push_back("most compact cars");
        compatibleVehicles.push_back("sedan");
    }
    
    // Устанавливаем список совместимости в базовый класс
    setCompatibilityList(compatibleVehicles);
}

std::string EnginePart::getType() const { 
    return "Engine: " + engineType; 
}

std::string EnginePart::getSpecifications() const { 
    return "Engine type: " + engineType + " | Compatible vehicles: " + 
           std::to_string(compatibleVehicles.size());
}

bool EnginePart::checkCompatibility(const std::string& vehicle) const {
    std::string vehicleLower = vehicle;
    std::transform(vehicleLower.begin(), vehicleLower.end(), vehicleLower.begin(), ::tolower);
    
    if (engineType == "V6") {
        if (vehicleLower.find("toyota") != std::string::npos || 
            vehicleLower.find("honda") != std::string::npos) return true;
    } else if (engineType.find("EJ") != std::string::npos) {
        if (vehicleLower.find("subaru") != std::string::npos) return true;
    } else if (engineType == "V12") {
        if (vehicleLower.find("ferrari") != std::string::npos || 
            vehicleLower.find("lamborghini") != std::string::npos) return true;
    } else if (engineType == "L4") {
        if (vehicleLower.find("compact") != std::string::npos || 
            vehicleLower.find("sedan") != std::string::npos) return true;
    }
    
    return AutoPart::checkCompatibility(vehicle);
}

std::string EnginePart::getCompatibilityInfo() const {
    return "Engine specific compatibility: " + std::to_string(compatibleVehicles.size()) + " vehicles";
}

std::string EnginePart::getDetailedInfo() const {
    std::string baseInfo = AutoPart::getDetailedInfo();
    return baseInfo + " | Engine type: " + engineType;
}

void EnginePart::addCompatibleVehicle(const std::string& vehicle) {
    compatibleVehicles.push_back(vehicle);
    addCompatibility(vehicle);
}

EnginePart& EnginePart::operator=(const EnginePart& other) {
    if (this != &other) {
        AutoPart::operator=(other);
        engineType = other.engineType;
        compatibleVehicles = other.compatibleVehicles;
    }
    return *this;
}