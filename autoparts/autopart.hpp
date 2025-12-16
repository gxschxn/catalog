#pragma once

#include <string>
#include <memory>
#include <iostream>

class AutoPart {
protected:
    std::string id;
    std::string name;
    double price;
    int quantity;
    
public:
    AutoPart(std::string id, std::string name, double price);
    virtual ~AutoPart() = default;
    
    // Конструктор копирования
    AutoPart(const AutoPart& other);
    
    double getPrice() const;
    bool isAvailable() const;
    std::string getFullInfo() const;
    bool isValid() const;
    
    // Перегрузка операторов
    bool operator==(const AutoPart& other) const;
    bool operator!=(const AutoPart& other) const;
    bool operator<(const AutoPart& other) const;
    
    // Дружественная функция для вывода
    friend std::ostream& operator<<(std::ostream& os, const AutoPart& part);
    
    virtual bool isCompatibleWith(const std::string& vehicle) const = 0;
    virtual std::string getType() const = 0;
    
    // Геттеры для доступа к полям
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }
};