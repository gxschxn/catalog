#include "catalog.hpp"

void Catalog::addPart(std::unique_ptr<AutoPart> part) {
    parts[part->getFullInfo()] = std::move(part);
}

AutoPart* Catalog::findPart(const string& name) {
    auto it = parts.find(name);
    return (it != parts.end()) ? it->second.get() : nullptr;
}

vector<AutoPart*> Catalog::findCompatible(const string& vehicle) {
    vector<AutoPart*> result;
    for (const auto& pair : parts) {
        if (pair.second->isCompatibleWith(vehicle)) {
            result.push_back(pair.second.get());
        }
    }
    return result;
}

size_t Catalog::getSize() const { return parts.size(); }