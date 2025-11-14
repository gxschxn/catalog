#pragma once

#include "autopart.hpp"
#include <vector>
#include <string>

class EnginePart : public AutoPart {
private:
    string engineType;
    vector<string> compatibleVehicles;
    
public:
    EnginePart(int id, string name, double price, string engineType);
    bool isCompatibleWith(const string& vehicle) const override;
    PartType getType() const override;
    void addVehicle(const string& vehicle);
};