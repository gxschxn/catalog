#include "autopart.hpp"
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

AutoPart::AutoPart(std::string id, std::string name, double price) 
    : id(id), name(name), price(price), quantity(0) {
}

AutoPart::~AutoPart() {
    // Деструктор
}

double AutoPart::getPrice() const { 
    return price; 
}

bool AutoPart::isAvailable() const { 
    return quantity > 0; 
}

std::string AutoPart::getFullInfo() const { 
    std::ostringstream oss;
    oss << name << " - " << std::fixed << std::setprecision(0) 
        << price << " RUB (" << id << ")";
    return oss.str();
}

bool AutoPart::isValid() const { 
    return !id.empty() && price > 0 && !name.empty();
}

bool AutoPart::checkCompatibility(const std::string& vehicle) const {
    std::string vehicleLower = vehicle;
    std::transform(vehicleLower.begin(), vehicleLower.end(), 
                   vehicleLower.begin(), ::tolower);
    
    for (const auto& compatibleVehicle : compatibilityList) {
        std::string compatibleLower = compatibleVehicle;
        std::transform(compatibleLower.begin(), compatibleLower.end(), 
                       compatibleLower.begin(), ::tolower);
        
        if (vehicleLower.find(compatibleLower) != std::string::npos ||
            compatibleLower.find(vehicleLower) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string AutoPart::getCompatibilityInfo() const {
    return "Compatible with " + std::to_string(compatibilityList.size()) + " vehicle types";
}

void AutoPart::displayInfo() const {
    std::cout << "Type: " << getType() << std::endl;
    std::cout << "Info: " << getFullInfo() << std::endl;
    std::cout << "Specs: " << getSpecifications() << std::endl;
}

std::string AutoPart::getDetailedInfo() const {
    return getFullInfo() + " | " + getCompatibilityInfo();
}

bool AutoPart::operator==(const AutoPart& other) const {
    return id == other.id && name == other.name && price == other.price;
}

bool AutoPart::operator!=(const AutoPart& other) const {
    return !(*this == other);
}

bool AutoPart::operator<(const AutoPart& other) const {
    if (price != other.price) {
        return price < other.price;
    }
    return name < other.name;
}

bool AutoPart::operator>(const AutoPart& other) const {
    if (price != other.price) {
        return price > other.price;
    }
    return name > other.name;
}

AutoPart& AutoPart::operator=(const AutoPart& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        price = other.price;
        quantity = other.quantity;
        compatibilityList = other.compatibilityList;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const AutoPart& part) {
    os << part.getFullInfo();
    return os;
}

void AutoPart::addCompatibility(const std::string& vehicle) {
    compatibilityList.push_back(vehicle);
}

void AutoPart::setCompatibilityList(const std::vector<std::string>& list) {
    compatibilityList = list;
}