#pragma once

#include "catalog.hpp"
#include "cart.hpp"
#include <vector>
#include <string>
#include <memory>

class AutoPartsApp {
private:
    Catalog catalog;
    Cart cart;
    
public:
    void addEnginePart(std::string id, std::string brand, std::string name, double price, std::string type);
    void addWheelPart(std::string id, std::string brand, std::string name, double price, double diameter, std::string bolts);
    
    std::vector<std::shared_ptr<AutoPart>> findForVehicle(const std::string& vehicle);
    void addToCart(const std::string& partId, int qty = 1);  // Меняем на поиск по ID
    void checkout();
    void showStats();
    
    // Методы для демонстрации
    void demonstratePartInventory();
    
    // Геттеры
    Catalog& getCatalog() { return catalog; }
    Cart& getCart() { return cart; }
};