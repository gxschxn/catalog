#include "cart.hpp"
#include <iostream>
#include <iomanip>

void Cart::addItem(std::shared_ptr<AutoPart> part, int qty) {
    if (part && part->isValid()) {
        // Проверяем, что не превышаем доступное количество
        int currentInCart = items[part];
        int totalRequested = currentInCart + qty;
        
        if (totalRequested > part->getAvailableQuantity()) {
            std::cout << "Error: Cannot add " << qty << " more items. "
                      << "Already have " << currentInCart << " in cart, "
                      << "only " << part->getAvailableQuantity() << " available total.\n";
            return;
        }
        
        items[part] += qty;
        operationHistory.push_back("Added: " + part->getFullName() + " x" + std::to_string(qty));
        std::cout << "Successfully added " << qty << " x " << part->getFullName() << " to cart.\n";
    }
}

void Cart::removeItem(std::shared_ptr<AutoPart> part) {
    if (part) {
        items.erase(part);
        operationHistory.push_back("Removed: " + part->getFullName());
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
                os << "  " << item.first->getId() << " - " 
                   << item.first->getFullName() << " x " << item.second 
                   << " = " << std::fixed << std::setprecision(0) 
                   << item.first->getPrice() * item.second << " руб.\n";
            }
        });
    
    os << "Итого: " << std::fixed << std::setprecision(0) << cart.getTotal() << " руб.";
    return os;
}