#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>

// Сначала объявим класс CloneablePart
class CloneablePart {
public:
    virtual ~CloneablePart() = default;
    virtual CloneablePart* deepClone() const = 0;
    virtual CloneablePart* shallowClone() const = 0;
};

class AutoPart : public CloneablePart {  // AutoPart теперь наследует CloneablePart
protected:
    std::string id;
    std::string name;
    double price;
    int quantity;
    std::vector<std::string> compatibilityList;
    
public:
    AutoPart(std::string id, std::string name, double price);
    
    virtual ~AutoPart();
    
    AutoPart(const AutoPart& other) = delete;
    
    double getPrice() const;
    bool isAvailable() const;
    std::string getFullInfo() const;
    bool isValid() const;
    
    virtual bool isCompatibleWith(const std::string& vehicle) const = 0;
    virtual std::string getType() const = 0;
    
    // теперь это часть интерфейса CloneablePart
    CloneablePart* deepClone() const override = 0;
    CloneablePart* shallowClone() const override = 0;
    
    // оставляем для удобства
    virtual AutoPart* clone() const = 0;
    
    void displayInfo() const;
    
    virtual std::string getDetailedInfo() const;
    
    bool operator==(const AutoPart& other) const;
    bool operator!=(const AutoPart& other) const;
    bool operator<(const AutoPart& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const AutoPart& part);
    
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }
    
    AutoPart& operator=(const AutoPart& other);
    
protected:
    void addCompatibility(const std::string& vehicle);
    void setCompatibilityList(const std::vector<std::string>& list);
};