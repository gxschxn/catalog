#pragma once

#include "autopart.hpp"
#include <string>

class Wheel : public AutoPart {
private:
    double diameter;
    std::string boltPattern;
    
public:
    Wheel(std::string id, std::string brand, std::string name, double price, double diameter, std::string boltPattern);
    
    Wheel(const Wheel& other) = delete;  // Оставляем удаленным
    
    // Реализация чисто виртуальных методов
    std::string getType() const override;
    std::string getSpecifications() const override;
    
    // Переопределение метода интерфейса
    bool checkCompatibility(const std::string& vehicle) const override;
    
    // Специфичные методы
    std::string getSpecs() const;
    double getDiameter() const { return diameter; }
    std::string getBoltPattern() const { return boltPattern; }
    
    Wheel& operator=(const Wheel& other);
    
    // Убираем оператор +, оставляем только >
    bool operator>(const Wheel& other) const;
};