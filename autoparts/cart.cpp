#include "cart.hpp"
#include <iostream>
#include <iomanip>

void Cart::addItem(std::shared_ptr<AutoPart> part, int qty) {
    if (part && part->isValid()) {
        items[part] += qty;
    }
}

void Cart::removeItem(std::shared_ptr<AutoPart> part) {
    if (part) {
        items.erase(part);
    }
}

void Cart::clear() {
    items.clear();
}

size_t Cart::getItemCount() const {
    return items.size();
}

double Cart::getTotal() const {
    double total = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->first) {
            total += it->first->getPrice() * it->second;
        }
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << "Содержимое корзины (" << cart.items.size() << " позиций):\n";
    for (auto it = cart.items.begin(); it != cart.items.end(); ++it) {
        if (it->first) {
            os << "  " << it->first->getName() << " x " << it->second 
               << " = " << std::fixed << std::setprecision(0) 
               << it->first->getPrice() * it->second << " руб.\n";
        }
    }
    os << "Итого: " << std::fixed << std::setprecision(0) << cart.getTotal() << " руб.";
    return os;
}