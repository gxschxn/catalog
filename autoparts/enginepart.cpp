#include "enginepart.hpp"

EnginePart::EnginePart(int id, string name, double price, string engineType)
    : AutoPart(id, name, price), engineType(engineType) {
    // автоматическое добавление совместимых авто в зависимости от типа двигателя
    if (engineType == "V6") {
        compatibleVehicles.push_back("toyota camry sedan");
        compatibleVehicles.push_back("toyota rav4");
        compatibleVehicles.push_back("honda accord sedan");
    } else if (engineType.find("EJ") != string::npos) {
        compatibleVehicles.push_back("subaru impreza");
        compatibleVehicles.push_back("subaru forester");
        compatibleVehicles.push_back("subaru wrx");
    } else if (engineType == "V12") {
        compatibleVehicles.push_back("ferrari 488");
        compatibleVehicles.push_back("lamborghini aventador");
    }
}

bool EnginePart::isCompatibleWith(const string& vehicle) const {
    // проверка по ключевым словам
    if (engineType == "V6") {
        if (vehicle.find("toyota") != string::npos || 
            vehicle.find("honda") != string::npos ||
            vehicle.find("nissan") != string::npos) return true;
    } else if (engineType.find("EJ") != string::npos) {
        if (vehicle.find("subaru") != string::npos) return true;
    } else if (engineType == "V12") {
        if (vehicle.find("ferrari") != string::npos || 
            vehicle.find("lamborghini") != string::npos) return true;
    }
    
    // проверка по точному совпадению
    for (const auto& v : compatibleVehicles) {
        if (v == vehicle) return true;
    }
    return false;
}

PartType EnginePart::getType() const { return PartType::ENGINE; }

void EnginePart::addVehicle(const string& vehicle) { 
    compatibleVehicles.push_back(vehicle); 
}