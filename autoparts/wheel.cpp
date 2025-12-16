#include "wheel.hpp"
#include <algorithm>

// Вызов конструктора базового класса
Wheel::Wheel(std::string id, std::string name, double price, double diameter, std::string boltPattern)
    : AutoPart(id, name, price), diameter(diameter), boltPattern(boltPattern) {}

// Конструктор копирования
Wheel::Wheel(const Wheel& other)
    : AutoPart(other), diameter(other.diameter), boltPattern(other.boltPattern) {}

bool Wheel::isCompatibleWith(const std::string& vehicle) const {
    std::string vehicleLower = vehicle;
    std::transform(vehicleLower.begin(), vehicleLower.end(), vehicleLower.begin(), ::tolower);
    
    return (vehicleLower.find("sedan") != std::string::npos && diameter >= 16.0) ||
           (vehicleLower.find("suv") != std::string::npos && diameter >= 17.0);
}

std::string Wheel::getType() const { 
    return "Wheel: " + std::to_string(static_cast<int>(diameter)) + " inch"; 
}

std::string Wheel::getSpecs() const { 
    return std::to_string(static_cast<int>(diameter)) + " inch, " + boltPattern; 
}

// Перегрузка операторов
Wheel Wheel::operator+(const Wheel& other) const {
    // Создание "комплекта" колес с объединенной спецификацией
    std::string newId = id + "_" + other.id;
    std::string newName = name + " & " + other.name + " Combo";
    double newPrice = price + other.price;
    double avgDiameter = (diameter + other.diameter) / 2;
    std::string newBoltPattern = boltPattern + "/" + other.boltPattern;
    
    return Wheel(newId, newName, newPrice, avgDiameter, newBoltPattern);
}

bool Wheel::operator>(const Wheel& other) const {
    return diameter > other.diameter;
}