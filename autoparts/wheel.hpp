#pragma once

#include "autopart.hpp"
#include <string>

class Wheel : public AutoPart {
private:
    double diameter;
    string boltPattern;
    
public:
    Wheel(int id, string name, double price, double diameter, string boltPattern);
    bool isCompatibleWith(const string& vehicle) const override;
    PartType getType() const override;
    string getSpecs() const;
};