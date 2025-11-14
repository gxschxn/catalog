#pragma once

#include <string>
using namespace std;

enum class PartType {
    ENGINE = 1,     
    WHEEL = 2,
    SUSPENSION = 3,
    BODY = 4
};

class AutoPart {
protected:
    int id;
    string name;
    double price;
    int quantity;
    
public:
    AutoPart(int id, string name, double price);
    virtual ~AutoPart() = default;
    
    double getPrice() const;
    bool isAvailable() const;
    string getFullInfo() const;
    bool isValid() const;
    
    virtual bool isCompatibleWith(const string& vehicle) const = 0;
    virtual PartType getType() const = 0;
};

string partTypeToString(PartType type);