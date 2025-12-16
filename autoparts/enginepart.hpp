#pragma once

#include "autopart.hpp"
#include <vector>
#include <string>
#include <memory>

class EnginePart : public AutoPart {
private:
    std::string engineType;
    std::vector<std::string> compatibleVehicles;
    
public:
    EnginePart(std::string id, std::string name, double price, std::string engineType);
    
    // Конструктор копирования
    EnginePart(const EnginePart& other);
    
    bool isCompatibleWith(const std::string& vehicle) const override;
    std::string getType() const override;
    void addVehicle(const std::string& vehicle);
    
    // Перегрузка операторов
    EnginePart& operator=(const EnginePart& other);
    
    // Дружественная функция
    friend bool isHighPerformanceEngine(const EnginePart& engine);
};