#pragma once

#include "autopart.hpp"
#include <string>

class Wheel : public AutoPart {
private:
    double diameter;
    std::string boltPattern;
    
public:
    Wheel(std::string id, std::string name, double price, double diameter, std::string boltPattern);
    
    // Конструктор копирования
    Wheel(const Wheel& other);
    
    bool isCompatibleWith(const std::string& vehicle) const override;
    std::string getType() const override;
    std::string getSpecs() const;
    
    // Перегрузка операторов
    Wheel operator+(const Wheel& other) const; // для создания комплекта
    bool operator>(const Wheel& other) const;
};