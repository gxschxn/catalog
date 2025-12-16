#include "enginepart.hpp"
#include <algorithm>
#include <iostream>

EnginePart::EnginePart(std::string id, std::string name, double price, std::string engineType)
    : AutoPart(id, name, price), engineType(engineType) {
    
    compatibleVehicles = new std::vector<std::string>();
    initializeCompatibility();
    addCompatibility("universal");
}

EnginePart::~EnginePart() {
    delete compatibleVehicles;
}

void EnginePart::initializeCompatibility() {
    if (engineType == "V6") {
        compatibleVehicles->push_back("toyota camry");
        compatibleVehicles->push_back("toyota rav4");
        compatibleVehicles->push_back("honda accord");
    } else if (engineType.find("EJ") != std::string::npos) {
        compatibleVehicles->push_back("subaru impreza");
        compatibleVehicles->push_back("subaru forester");
    } else if (engineType == "V12") {
        compatibleVehicles->push_back("ferrari 488");
        compatibleVehicles->push_back("lamborghini aventador");
    }
}

bool EnginePart::isCompatibleWith(const std::string& vehicle) const {
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
    }
    
    return std::find(compatibleVehicles->begin(), compatibleVehicles->end(), vehicleLower) 
           != compatibleVehicles->end();
}

std::string EnginePart::getType() const { 
    return "Engine: " + engineType; 
}

std::string EnginePart::getDetailedInfo() const {
    std::string baseInfo = AutoPart::getDetailedInfo();
    return baseInfo + " | Engine type: " + engineType;
}

std::string EnginePart::getFullInfo() const {
    return name + " [" + engineType + "] - " + 
           std::to_string(static_cast<int>(price)) + " RUB (" + id + ")";
}

AutoPart* EnginePart::clone() const {
    EnginePart* newPart = new EnginePart(id, name, price, engineType);
    newPart->setQuantity(quantity);
    
    std::vector<std::string>* newList = new std::vector<std::string>(*compatibleVehicles);
    delete newPart->compatibleVehicles;
    newPart->compatibleVehicles = newList;
    
    return newPart;
}

CloneablePart* EnginePart::deepClone() const {
    return this->clone();
}

CloneablePart* EnginePart::shallowClone() const {
    EnginePart* newPart = new EnginePart(id, name, price, engineType);
    newPart->compatibleVehicles = this->compatibleVehicles;
    return newPart;
}

EnginePart& EnginePart::operator=(const AutoPart& other) {
    if (this != &other) {
        AutoPart::operator=(other);
        engineType = "Unknown";
    }
    return *this;
}

EnginePart& EnginePart::operator=(const EnginePart& other) {
    if (this != &other) {
        AutoPart::operator=(other);
        engineType = other.engineType;
        delete compatibleVehicles;
        compatibleVehicles = new std::vector<std::string>(*other.compatibleVehicles);
    }
    return *this;
}

void EnginePart::addVehicle(const std::string& vehicle) { 
    compatibleVehicles->push_back(vehicle); 
}

bool isHighPerformanceEngine(const EnginePart& engine) {
    return engine.engineType == "V12" || engine.engineType.find("turbo") != std::string::npos;
}