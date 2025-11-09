#pragma once

#include "autopart.hpp"
#include <unordered_map>

class Cart {
private:
    std::unordered_map<AutoPart*, int> items;
    
public:
    void addItem(AutoPart* part, int qty = 1);
    void removeItem(AutoPart* part);
    double getTotal() const;
    void clear();
    size_t getItemCount() const;
};