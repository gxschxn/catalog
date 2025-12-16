#pragma once

#include "autopart.hpp"
#include <unordered_map>
#include <memory>

class Cart {
private:
    // Замена сырых указателей на shared_ptr
    std::unordered_map<std::shared_ptr<AutoPart>, int> items;
    
public:
    void addItem(std::shared_ptr<AutoPart> part, int qty = 1);
    void removeItem(std::shared_ptr<AutoPart> part);
    double getTotal() const;
    void clear();
    size_t getItemCount() const;
    
    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
};