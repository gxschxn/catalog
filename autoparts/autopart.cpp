#include "autopart.hpp"
#include <string>
#include <algorithm>

AutoPart::AutoPart(std::string id, std::string name, double price) 
    : id(id), name(name), price(price), quantity(0) {
}

AutoPart::~AutoPart() {
    // Убираем вывод для чистоты
}

double AutoPart::getPrice() const { 
    return price; 
}

bool AutoPart::isAvailable() const { 
    return quantity > 0; 
}

std::string AutoPart::getFullInfo() const { 
    return name + " - " + std::to_string(static_cast<int>(price)) + " RUB (" + id + ")";
}

bool AutoPart::isValid() const { 
    return !id.empty() && price > 0 && !name.empty();
}

void AutoPart::displayInfo() const {
    std::cout << "Type: " << getType() << std::endl;
    std::cout << "Info: " << getFullInfo() << std::endl;
}

std::string AutoPart::getDetailedInfo() const {
    return getFullInfo() + " | Compatible with " + std::to_string(compatibilityList.size()) + " vehicles";
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