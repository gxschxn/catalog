#include "autopartsapp.hpp"
#include "enginepart.hpp"
#include "wheel.hpp"
#include <iostream>
#include <memory>

void AutoPartsApp::addEnginePart(int id, std::string name, double price, std::string type) {
    catalog.addPart(std::unique_ptr<EnginePart>(new EnginePart (id, name, price, type)));
}

void AutoPartsApp::addWheelPart(int id, std::string name, double price, double diameter, std::string bolts) {
    catalog.addPart(std::unique_ptr<Wheel>(new Wheel (id, name, price, diameter, bolts)));
}

std::vector<AutoPart*> AutoPartsApp::findForVehicle(const std::string& vehicle) {
    return catalog.findCompatible(vehicle);
}

void AutoPartsApp::addToCart(const std::string& partName, int qty) {
    if (AutoPart* part = catalog.findPart(partName)) {
        cart.addItem(part, qty);
    }
}

void AutoPartsApp::checkout() {
    std::cout << "Order total: " << cart.getTotal() << " руб." << std::endl;
    cart.clear();
}

void AutoPartsApp::showStats() {
    std::cout << "Catalog size: " << catalog.getSize() 
              << ", Cart items: " << cart.getItemCount() << std::endl;
}