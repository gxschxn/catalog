#include "autopart.hpp"
#include <string>

AutoPart::AutoPart(string id, string name, double price) 
    : id(id), name(name), price(price), quantity(0) {}

double AutoPart::getPrice() const { return price; }

bool AutoPart::isAvailable() const { return quantity > 0; }

string AutoPart::getFullInfo() const { 
    return name + " - " + to_string((int)price) + " руб. (" + id + ")"; 
}

bool AutoPart::isValid() const { return !id.empty() && price > 0; }