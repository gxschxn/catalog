#pragma once

#include "autopart.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

class Catalog {
private:
    unordered_map<string, unique_ptr<AutoPart>> parts;
    
public:
    void addPart(unique_ptr<AutoPart> part);
    AutoPart* findPart(const string& name);
    vector<AutoPart*> findCompatible(const string& vehicle);
    size_t getSize() const;
};