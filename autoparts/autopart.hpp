#pragma once

#include <string>
using namespace std;

class AutoPart {
protected:
    string id;
    string name;
    double price;
    int quantity;
    
public:
    AutoPart(string id, string name, double price);
    virtual ~AutoPart() = default;
    
    double getPrice() const;
    bool isAvailable() const;
    string getFullInfo() const;
    bool isValid() const;
    
    virtual bool isCompatibleWith(const string& vehicle) const = 0;
    virtual string getType() const = 0;
};