#pragma once

#include "autopart.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

class Cart {
private:
    std::unordered_map<std::shared_ptr<AutoPart>, int> items;
    std::list<std::string> operationHistory;
    
public:
    Cart() = default;
    
    void addItem(std::shared_ptr<AutoPart> part, int qty = 1);
    void removeItem(std::shared_ptr<AutoPart> part);
    void clear();
    
    size_t getItemCount() const { return items.size(); }
    
    double getTotal() const {
        return std::accumulate(items.begin(), items.end(), 0.0,
            [](double total, const auto& item) {
                return total + (item.first->getPrice() * item.second);
            });
    }
    
    // Методы с использованием алгоритмов STL
    double getTotalWithDiscount(double discountPercent) const {
        double total = getTotal();
        return calculateDiscountedPrice(total, discountPercent);
    }
    
    std::vector<std::shared_ptr<AutoPart>> getSortedByPrice(bool ascending = true) const {
        std::vector<std::shared_ptr<AutoPart>> result;
        result.reserve(items.size());
        
        for (const auto& item : items) {
            result.push_back(item.first);
        }
        
        std::sort(result.begin(), result.end(),
            [ascending](const std::shared_ptr<AutoPart>& a,
                        const std::shared_ptr<AutoPart>& b) {
                if (ascending) {
                    return a->getPrice() < b->getPrice();
                } else {
                    return a->getPrice() > b->getPrice();
                }
            });
        
        return result;
    }
    
    bool hasExpensiveItems(double threshold) const {
        return std::any_of(items.begin(), items.end(),
            [threshold](const auto& item) {
                return item.first->getPrice() > threshold;
            });
    }
    
    const std::list<std::string>& getOperationHistory() const { return operationHistory; }
    
    friend std::ostream& operator<<(std::ostream& os, const Cart& cart);
};