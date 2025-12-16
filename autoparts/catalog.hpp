#pragma once

#include "autopart.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

class Catalog {
private:
    // Использование unique_ptr для исключительного владения
    std::unordered_map<std::string, std::unique_ptr<AutoPart>> parts;
    
public:
    void addPart(std::unique_ptr<AutoPart> part);
    std::shared_ptr<AutoPart> findPart(const std::string& name);
    std::vector<std::shared_ptr<AutoPart>> findCompatible(const std::string& vehicle);
    size_t getSize() const;
    
    // Перегрузка оператора []
    std::shared_ptr<AutoPart> operator[](const std::string& partName);
};