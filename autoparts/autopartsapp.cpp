#include "autopartsapp.hpp"
#include "enginepart.hpp"
#include "wheel.hpp"
#include <iostream>
#include <memory>
#include <iomanip>  // для std::fixed и std::setprecision

void AutoPartsApp::addEnginePart(std::string id, std::string name, double price, std::string type) {
    catalog.addPart(std::make_unique<EnginePart>(id, name, price, type));
}

void AutoPartsApp::addWheelPart(std::string id, std::string name, double price, double diameter, std::string bolts) {
    catalog.addPart(std::make_unique<Wheel>(id, name, price, diameter, bolts));
}

std::vector<std::shared_ptr<AutoPart>> AutoPartsApp::findForVehicle(const std::string& vehicle) {
    return catalog.findCompatible(vehicle);
}

void AutoPartsApp::addToCart(const std::string& partName, int qty) {
    if (auto part = catalog.findPart(partName)) {
        cart.addItem(part, qty);
    }
}

void AutoPartsApp::checkout() {
    double total = cart.getTotal();
    // Исправляем форматирование вывода
    std::cout << "Сумма заказа: " << std::fixed << std::setprecision(0) << total << " руб." << std::endl;
    cart.clear();
}

void AutoPartsApp::showStats() {
    std::cout << "Каталог: " << catalog.getSize() 
              << " товаров, Корзина: " << cart.getItemCount() << " позиций" << std::endl;
}