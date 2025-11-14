#include "cart.hpp"

void Cart::addItem(AutoPart* part, int qty) {
    items[part] += qty;
}

void Cart::removeItem(AutoPart* part) {
    items.erase(part);
}

double Cart::getTotal() const {
    double total = 0;
    for (const auto& item : items) {
        total += item.first->getPrice() * item.second;
    }
    return total;
}

void Cart::clear() { 
    items.clear(); 
}

size_t Cart::getItemCount() const { 
    return items.size(); 
}