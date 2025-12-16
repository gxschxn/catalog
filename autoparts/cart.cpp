#include "cart.hpp"
#include <iostream>

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

double Cart::getTotal() const {
    double total = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->first) {
            total += it->first->getPrice() * it->second;
        }
    }
    return total;
}

void Cart::clear() { 
    items.clear(); 
}

size_t Cart::getItemCount() const { 
    return items.size(); 
}

// Дружественная функция для вывода корзины
std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << "Cart contents (" << cart.items.size() << " items):\n";
    for (auto it = cart.items.begin(); it != cart.items.end(); ++it) {
        if (it->first) {
            os << "  " << it->first->getName() << " x " << it->second 
               << " = " << it->first->getPrice() * it->second << " rub.\n";
        }
    }
    os << "Total: " << cart.getTotal() << " rub.";
    return os;
}