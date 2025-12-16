#pragma once

#include "autopart.hpp"
#include <string>

class Wheel : public AutoPart {
private:
    double diameter;
    std::string boltPattern;
    
public:
    Wheel(std::string id, std::string name, double price, double diameter, std::string boltPattern);
    
    Wheel(const Wheel& other) = delete;
    
    bool isCompatibleWith(const std::string& vehicle) const override;
    std::string getType() const override;
    
    // реализуем интерфейс CloneablePart
    CloneablePart* deepClone() const override;
    CloneablePart* shallowClone() const override;
    
    // и наш метод
    AutoPart* clone() const override;
    
    std::string getSpecs() const;
    
    Wheel* operator+(const Wheel& other) const;
    bool operator>(const Wheel& other) const;
    
    std::string getSpecialInfo() const;
    virtual std::string getSpecialInfoVirtual() const;
};