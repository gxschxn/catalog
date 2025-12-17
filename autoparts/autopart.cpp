#include "autopart.hpp"
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>

static_assert(AutoPart::MAX_BATCH_SIZE > 0, "Batch size must be positive");

AutoPart::AutoPart(std::string id, std::string brand, std::string name, double price) 
    : id(id), brand(brand), name(name), price(price), quantity(0) {
    // Используем constexpr функцию для валидации
    if (!isValidPrice(price)) {
        throw std::invalid_argument("Invalid price value. Price must be between " + 
                                   std::to_string(MIN_PRICE) + " and " + 
                                   std::to_string(MAX_PRICE));
    }
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
    oss << brand << " " << name << " (" << id << ") - " 
        << std::fixed << std::setprecision(0) << price << " RUB";
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