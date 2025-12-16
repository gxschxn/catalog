#include "enginepart.hpp"
#include <algorithm> // для std::find

// Вызов конструктора базового класса из конструктора дочернего класса
EnginePart::EnginePart(std::string id, std::string name, double price, std::string engineType)
    : AutoPart(id, name, price), engineType(engineType) {
    
    // Использование методов std::string для поиска
    if (engineType == "V6") {
        compatibleVehicles.push_back("toyota camry sedan");
        compatibleVehicles.push_back("toyota rav4");
        compatibleVehicles.push_back("honda accord sedan");
    } else if (engineType.find("EJ") != std::string::npos) {
        compatibleVehicles.push_back("subaru impreza");
        compatibleVehicles.push_back("subaru forester");
        compatibleVehicles.push_back("subaru wrx");
    } else if (engineType == "V12") {
        compatibleVehicles.push_back("ferrari 488");
        compatibleVehicles.push_back("lamborghini aventador");
    }
}

// Конструктор копирования
EnginePart::EnginePart(const EnginePart& other)
    : AutoPart(other), // вызов конструктора копирования базового класса
      engineType(other.engineType),
      compatibleVehicles(other.compatibleVehicles) {}

bool EnginePart::isCompatibleWith(const std::string& vehicle) const {
    // Использование методов std::string для поиска подстрок
    std::string vehicleLower = vehicle;
    std::transform(vehicleLower.begin(), vehicleLower.end(), vehicleLower.begin(), ::tolower);
    
    if (engineType == "V6") {
        if (vehicleLower.find("toyota") != std::string::npos || 
            vehicleLower.find("honda") != std::string::npos ||
            vehicleLower.find("nissan") != std::string::npos) return true;
    } else if (engineType.find("EJ") != std::string::npos) {
        if (vehicleLower.find("subaru") != std::string::npos) return true;
    } else if (engineType == "V12") {
        if (vehicleLower.find("ferrari") != std::string::npos || 
            vehicleLower.find("lamborghini") != std::string::npos) return true;
    }
    
    // Поиск точного совпадения в векторе
    return std::find(compatibleVehicles.begin(), compatibleVehicles.end(), vehicleLower) != compatibleVehicles.end();
}

std::string EnginePart::getType() const { 
    return "Engine Part: " + engineType; 
}

void EnginePart::addVehicle(const std::string& vehicle) { 
    compatibleVehicles.push_back(vehicle); 
}

// Перегрузка оператора присваивания
EnginePart& EnginePart::operator=(const EnginePart& other) {
    if (this != &other) {
        AutoPart::operator=(other); // вызов оператора присваивания базового класса
        engineType = other.engineType;
        compatibleVehicles = other.compatibleVehicles;
    }
    return *this;
}

// Дружественная функция
bool isHighPerformanceEngine(const EnginePart& engine) {
    return engine.engineType == "V12" || engine.engineType.find("turbo") != std::string::npos;
}