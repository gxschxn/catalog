#include "autopartsapp.hpp"
#include "enginepart.hpp"
#include "wheel.hpp"
#include <iostream>
#include <memory>
#include <iomanip>
#include <algorithm>

void AutoPartsApp::addEnginePart(std::string id, std::string brand, std::string name, double price, std::string type) {
    auto part = std::make_unique<EnginePart>(id, brand, name, price, type);
    catalog.addPart(std::move(part));
}

void AutoPartsApp::addWheelPart(std::string id, std::string brand, std::string name, double price, double diameter, std::string bolts) {
    auto part = std::make_unique<Wheel>(id, brand, name, price, diameter, bolts);
    catalog.addPart(std::move(part));
}

std::vector<std::shared_ptr<AutoPart>> AutoPartsApp::findForVehicle(const std::string& vehicle) {
    return catalog.findCompatible(vehicle);
}

void AutoPartsApp::addToCart(const std::string& partId, int qty) {
    auto part = catalog.findPartById(partId);
    if (part) {
        // Проверяем наличие
        if (!part->isAvailable()) {
            std::cout << "Error: Part '" << part->getFullName() << "' is out of stock!\n";
            return;
        }
        
        // Проверяем, что запрашиваемое количество не превышает доступное
        if (qty > part->getAvailableQuantity()) {
            std::cout << "Error: Only " << part->getAvailableQuantity() 
                      << " items available. Cannot add " << qty << " to cart.\n";
            return;
        }
        
        cart.addItem(part, qty);
    } else {
        std::cout << "Error: Part with ID " << partId << " not found!\n";
    }
}

void AutoPartsApp::checkout() {
    double total = cart.getTotal();
    
    // Применяем шаблонную функцию для скидки
    double discount = 0.0;
    if (total > 500000) discount = 10.0;
    else if (total > 200000) discount = 5.0;
    
    double finalTotal = cart.getTotalWithDiscount(discount);
    
    std::cout << "Сумма заказа: " << std::fixed << std::setprecision(0) << total << " руб." << std::endl;
    std::cout << "Скидка: " << discount << "%" << std::endl;
    std::cout << "Итого к оплате: " << finalTotal << " руб." << std::endl;
    
    cart.clear();
}

void AutoPartsApp::showStats() {
    std::cout << "Каталог: " << catalog.getSize() 
              << " товаров, Корзина: " << cart.getItemCount() << " позиций" << std::endl;
}

void AutoPartsApp::demonstratePartInventory() {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ ШАБЛОННОГО КЛАССА PARTINVENTORY ===" << std::endl;
    
    // Создаем инвентарь для двигателей
    PartInventory<EnginePart> engineInventory;
    
    engineInventory.addPart("E001", "Toyota", "Двигатель V6", 350000, "V6");
    engineInventory.addPart("E002", "BMW", "Двигатель V8", 550000, "V8");
    engineInventory.addPart("E003", "Honda", "Двигатель L4", 180000, "L4");
    
    std::cout << "Всего двигателей: " << engineInventory.size() << std::endl;
    
    // Демонстрация поиска самой дорогой детали
    auto mostExpensive = engineInventory.findMostExpensive();
    if (mostExpensive) {
        std::cout << "Самый дорогой двигатель: " << mostExpensive->getFullName() 
                  << " (" << mostExpensive->getPrice() << " руб.)" << std::endl;
    }
    
    // Демонстрация фильтрации
    auto expensiveEngines = engineInventory.filterByMinPrice(300000);
    std::cout << "Двигатели дороже 300000 руб.: " << expensiveEngines.size() << " шт." << std::endl;
}