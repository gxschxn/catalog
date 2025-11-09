#pragma once

#include "catalog.hpp"
#include "cart.hpp"
#include <vector>
#include <string>

class AutoPartsApp {
private:
    Catalog catalog;
    Cart cart;
    
public:
    void addEnginePart(std::string id, std::string name, double price, std::string type);
    void addWheelPart(std::string id, std::string name, double price, double diameter, std::string bolts);
    std::vector<AutoPart*> findForVehicle(const std::string& vehicle);
    void addToCart(const std::string& partName, int qty = 1);
    void checkout();
    void showStats();
};