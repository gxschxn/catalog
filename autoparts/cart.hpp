#pragma once

#include "autopart.hpp"
#include <unordered_map>
#include <memory>

class Cart {
private:
    std::unordered_map<std::shared_ptr<AutoPart>, int> items;
    
public:
    void addItem(std::shared_ptr<AutoPart> part, int qty = 1);
    void removeItem(std::shared_ptr<AutoPart> part);
    void clear();  // Объявлен
    size_t getItemCount() const;  // Объявлен
    double getTotal() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
};