#include "catalog.hpp"
#include <algorithm>

void Catalog::addPart(std::unique_ptr<AutoPart> part) {
    if (part && part->isValid()) {
        std::string key = part->getFullInfo();
        parts[key] = std::move(part);
    }
}

std::shared_ptr<AutoPart> Catalog::findPart(const std::string& name) {
    auto it = parts.find(name);
    if (it != parts.end()) {
        return std::shared_ptr<AutoPart>(it->second.get(), [](AutoPart*){});
    }
    return nullptr;
}

std::vector<std::shared_ptr<AutoPart>> Catalog::findCompatible(const std::string& vehicle) {
    std::vector<std::shared_ptr<AutoPart>> result;
    for (const auto& pair : parts) {
        auto& part = pair.second;
        if (part->isCompatibleWith(vehicle)) {
            result.push_back(std::shared_ptr<AutoPart>(part.get(), [](AutoPart*){}));
        }
    }
    return result;
}

size_t Catalog::getSize() const { 
    return parts.size(); 
}

std::shared_ptr<AutoPart> Catalog::operator[](const std::string& partName) {
    return findPart(partName);
}