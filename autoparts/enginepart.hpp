#ifndef ENGINEPART_HPP
#define ENGINEPART_HPP

#include "autopart.hpp"
#include <vector>
#include <string>

class EnginePart : public AutoPart {
private:
    string engineType;
    vector<string> compatibleVehicles;
    
public:
    EnginePart(string id, string name, double price, string engineType);
    bool isCompatibleWith(const string& vehicle) const override;
    string getType() const override;
    void addVehicle(const string& vehicle);
};

#endif