#pragma once

#include "autopart.hpp"
#include <vector>
#include <string>

class EnginePart : public AutoPart {
private:
    std::string engineType;
    std::vector<std::string> compatibleVehicles;
    
public:
    EnginePart(std::string id, std::string brand, std::string name, double price, std::string engineType);
    
    virtual ~EnginePart() override;
    
    EnginePart(const EnginePart& other) = delete;
    
    // Реализация чисто виртуальных методов
    std::string getType() const override;
    std::string getSpecifications() const override;
    
    // Переопределение методов интерфейса
    bool checkCompatibility(const std::string& vehicle) const override;
    std::string getCompatibilityInfo() const override;
    
    // Перегрузка getDetailedInfo
    std::string getDetailedInfo() const override;
    
    // Специфичные методы
    std::string getEngineType() const { return engineType; }
    void addCompatibleVehicle(const std::string& vehicle);
    
    EnginePart& operator=(const EnginePart& other);
    
private:
    void initializeCompatibility();
};