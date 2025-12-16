#pragma once

#include "autopart.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>

class Catalog {
private:
    std::unordered_map<std::string, std::unique_ptr<AutoPart>> parts;
    std::list<std::string> recentAdditions;
    static const size_t maxRecentItems = 5;
    
public:
    Catalog() = default;
    
    // Конструктор перемещения
    Catalog(Catalog&& other) noexcept = default;
    Catalog& operator=(Catalog&& other) noexcept = default;
    
    // Запрещаем копирование
    Catalog(const Catalog&) = delete;
    Catalog& operator=(const Catalog&) = delete;
    
    void addPart(std::unique_ptr<AutoPart> part);
    std::shared_ptr<AutoPart> findPart(const std::string& name);
    std::vector<std::shared_ptr<AutoPart>> findCompatible(const std::string& vehicle);
    
    // Методы с использованием алгоритмов STL
    std::vector<std::shared_ptr<AutoPart>> getAllParts() const {
        std::vector<std::shared_ptr<AutoPart>> result;
        result.reserve(parts.size());
        
        for (const auto& pair : parts) {
            result.push_back(std::shared_ptr<AutoPart>(
                pair.second.get(), [](AutoPart*){}));
        }
        
        return result;
    }
    
    std::vector<std::shared_ptr<AutoPart>> getSortedByPrice(bool ascending = true) const {
        auto allParts = getAllParts();
        std::sort(allParts.begin(), allParts.end(),
            [ascending](const std::shared_ptr<AutoPart>& a,
                        const std::shared_ptr<AutoPart>& b) {
                if (ascending) {
                    return a->getPrice() < b->getPrice();
                } else {
                    return a->getPrice() > b->getPrice();
                }
            });
        return allParts;
    }
    
    std::shared_ptr<AutoPart> findMostExpensive() const {
        if (parts.empty()) return nullptr;
        
        auto it = std::max_element(parts.begin(), parts.end(),
            [](const auto& a, const auto& b) {
                return a.second->getPrice() < b.second->getPrice();
            });
        
        return std::shared_ptr<AutoPart>(it->second.get(), [](AutoPart*){});
    }
    
    bool hasExpensiveParts(double threshold) const {
        return std::any_of(parts.begin(), parts.end(),
            [threshold](const auto& pair) {
                return pair.second->getPrice() > threshold;
            });
    }
    
    size_t getSize() const { 
        return parts.size(); 
    }
    
    std::shared_ptr<AutoPart> operator[](const std::string& partName) {
        return findPart(partName);
    }
    
    const std::list<std::string>& getRecentAdditions() const {
        return recentAdditions;
    }
    
    // Метод для демонстрации шаблонов
    template<typename T>
    std::vector<std::shared_ptr<T>> getPartsOfType() const {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& pair : parts) {
            T* typed = dynamic_cast<T*>(pair.second.get());
            if (typed) {
                result.push_back(std::shared_ptr<T>(
                    typed, [](T*){}));
            }
        }
        return result;
    }
};