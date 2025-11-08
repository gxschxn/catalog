#ifndef WHEEL_HPP
#define WHEEL_HPP

#include "autopart.hpp"
#include <string>

class Wheel : public AutoPart {
private:
    double diameter;
    string boltPattern;
    
public:
    Wheel(string id, string name, double price, double diameter, string boltPattern);
    bool isCompatibleWith(const string& vehicle) const override;
    string getType() const override;
    string getSpecs() const;
};

#endif