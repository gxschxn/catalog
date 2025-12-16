#include "catalog.hpp"
#include <algorithm>
#include <iostream>

void Catalog::addPart(std::unique_ptr<AutoPart> part) {
    if (part && part->isValid()) {
        std::string key = part->getFullInfo();
        parts[key] = std::move(part);
        
        // Добавляем в историю (используем list)
        recentAdditions.push_back(key);
        if (recentAdditions.size() > maxRecentItems) {
            recentAdditions.pop_front();
        }
    }
}

std::shared_ptr<AutoPart> Catalog::findPart(const std::string& name) {
    auto it = parts.find(name);
    if (it != parts.end()) {
        return std::shared_ptr<AutoPart>(it->second.get(), [](AutoPart*){});
    }
    
    // Если не нашли по полному имени, ищем частичное совпадение
    for (const auto& pair : parts) {
        if (pair.second->getName().find(name) != std::string::npos) {
            return std::shared_ptr<AutoPart>(pair.second.get(), [](AutoPart*){});
        }
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