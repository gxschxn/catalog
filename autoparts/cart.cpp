#include "cart.hpp"
#include <iostream>
#include <iomanip>

void Cart::addItem(std::shared_ptr<AutoPart> part, int qty) {
    if (part && part->isValid()) {
        items[part] += qty;
        operationHistory.push_back("Added: " + part->getName() + " x" + std::to_string(qty));
    }
}

void Cart::removeItem(std::shared_ptr<AutoPart> part) {
    if (part) {
        items.erase(part);
        operationHistory.push_back("Removed: " + part->getName());
    }
}

void Cart::clear() {
    if (!items.empty()) {
        operationHistory.push_back("Cart cleared");
        items.clear();
    }
}

std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    os << "Корзина (" << cart.items.size() << " позиций):\n";
    
    // Используем for_each для вывода
    std::for_each(cart.items.begin(), cart.items.end(),
        [&os](const auto& item) {
            if (item.first) {
                os << "  " << item.first->getName() << " x " << item.second 
                   << " = " << std::fixed << std::setprecision(0) 
                   << item.first->getPrice() * item.second << " руб.\n";
            }
        });
    
    os << "Итого: " << std::fixed << std::setprecision(0) << cart.getTotal() << " руб.";
    return os;
}