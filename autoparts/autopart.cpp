#include "autopart.hpp"
#include <string>

AutoPart::AutoPart(int id, string name, double price) 
    : id(id), name(name), price(price), quantity(0) {}

double AutoPart::getPrice() const { return price; }

bool AutoPart::isAvailable() const { return quantity > 0; }

string AutoPart::getFullInfo() const { 
    return name + " - " + to_string((int)price) + " руб. (" + to_string(id) + ")"; 
}

bool AutoPart::isValid() const { return id > 0 && price > 0; }

string partTypeToString(PartType type) {
    switch(type) {
        case PartType::ENGINE: return "Engine";
        case PartType::WHEEL: return "Wheel";
        case PartType::SUSPENSION: return "Suspension";
        case PartType::BODY: return "Body";
        default: return "Unknown";
    }
}