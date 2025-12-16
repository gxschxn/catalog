#pragma once

#include "autopart.hpp"
#include <vector>
#include <string>
#include <memory>

class EnginePart : public AutoPart {
private:
    std::string engineType;
    std::vector<std::string>* compatibleVehicles;
    
public:
    EnginePart(std::string id, std::string name, double price, std::string engineType);
    
    virtual ~EnginePart();
    
    EnginePart(const EnginePart& other) = delete;
    
    bool isCompatibleWith(const std::string& vehicle) const override;
    std::string getType() const override;
    
    std::string getDetailedInfo() const override;
    
    std::string getFullInfo() const;
    
    // реализуем методы CloneablePart
    CloneablePart* deepClone() const override;
    CloneablePart* shallowClone() const override;
    
    // и наш собственный метод clone
    AutoPart* clone() const override;
    
    EnginePart& operator=(const AutoPart& other);
    EnginePart& operator=(const EnginePart& other);
    
    void addVehicle(const std::string& vehicle);
    
    friend bool isHighPerformanceEngine(const EnginePart& engine);
    
private:
    void initializeCompatibility();
};