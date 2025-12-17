#include "catalog.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

void Catalog::addPart(std::unique_ptr<AutoPart> part) {
    if (part && part->isValid()) {
        std::string key = part->getFullInfo();
        parts[key] = std::move(part);
        
        // Добавляем также в мапу для поиска по ID
        std::string id = parts[key]->getId();
        partsById[id] = parts[key].get();
        
        // Добавляем в историю
        recentAdditions.push_back(key);
        if (recentAdditions.size() > maxRecentItems) {
            recentAdditions.pop_front();
        }
    }
}

std::shared_ptr<AutoPart> Catalog::findPart(const std::string& name) {
    // Сначала ищем по полному имени
    auto it = parts.find(name);
    if (it != parts.end()) {
        return std::shared_ptr<AutoPart>(it->second.get(), [](AutoPart*){});
    }
    
    // Если не нашли по полному имени, ищем частичное совпадение
    for (const auto& pair : parts) {
        if (pair.second->getFullName().find(name) != std::string::npos) {
            return std::shared_ptr<AutoPart>(pair.second.get(), [](AutoPart*){});
        }
    }
    
    return nullptr;
}

std::shared_ptr<AutoPart> Catalog::findPartById(const std::string& id) {
    auto it = partsById.find(id);
    if (it != partsById.end()) {
        return std::shared_ptr<AutoPart>(it->second, [](AutoPart*){});
    }
    return nullptr;
}

std::vector<std::shared_ptr<AutoPart>> Catalog::findCompatible(const std::string& vehicle) {
    std::vector<std::shared_ptr<AutoPart>> result;
    
    // Используем алгоритм copy_if
    for (const auto& pair : parts) {
        if (pair.second->checkCompatibility(vehicle)) {
            result.push_back(std::shared_ptr<AutoPart>(pair.second.get(), [](AutoPart*){}));
        }
    }
    
    return result;
}

std::vector<std::shared_ptr<AutoPart>> Catalog::getAllParts() const {
    std::vector<std::shared_ptr<AutoPart>> result;
    result.reserve(parts.size());
    
    for (const auto& pair : parts) {
        result.push_back(std::shared_ptr<AutoPart>(
            pair.second.get(), [](AutoPart*){}));
    }
    
    return result;
}

std::vector<std::shared_ptr<AutoPart>> Catalog::getSortedByPrice(bool ascending) const {
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

std::shared_ptr<AutoPart> Catalog::findMostExpensive() const {
    if (parts.empty()) return nullptr;
    
    auto it = std::max_element(parts.begin(), parts.end(),
        [](const auto& a, const auto& b) {
            return a.second->getPrice() < b.second->getPrice();
        });
    
    return std::shared_ptr<AutoPart>(it->second.get(), [](AutoPart*){});
}

bool Catalog::hasExpensiveParts(double threshold) const {
    return std::any_of(parts.begin(), parts.end(),
        [threshold](const auto& pair) {
            return pair.second->getPrice() > threshold;
        });
}

size_t Catalog::getSize() const { 
    return parts.size(); 
}

std::shared_ptr<AutoPart> Catalog::operator[](const std::string& partName) {
    return findPart(partName);
}

const std::list<std::string>& Catalog::getRecentAdditions() const {
    return recentAdditions;
}

// Метод для демонстрации шаблонов
template<typename T>
std::vector<std::shared_ptr<T>> Catalog::getPartsOfType() const {
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

// Явная инстанциация шаблонного метода для компилятора
template std::vector<std::shared_ptr<EnginePart>> Catalog::getPartsOfType<EnginePart>() const;
template std::vector<std::shared_ptr<Wheel>> Catalog::getPartsOfType<Wheel>() const;