#include "autopartsapp.hpp"
#include "enginepart.hpp"
#include "wheel.hpp"
#include <iostream>
#include <memory>

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
    std::cout << "Order total: " << cart.getTotal() << " руб." << std::endl;
    cart.clear();
}

void AutoPartsApp::showStats() {
    std::cout << "Catalog size: " << catalog.getSize() 
              << ", Cart items: " << cart.getItemCount() << std::endl;
}

void AutoPartsApp::demonstrateStringOperations() {
    std::cout << "\n=== String Operations Demo ===" << std::endl;
    
    // Конкатенация строк
    std::string partType = "Engine";
    std::string partSubtype = "V6";
    std::string fullType = partType + " " + partSubtype;
    std::cout << "Concatenation: " << fullType << std::endl;
    
    // Поиск подстрок
    std::string vehicleInfo = "toyota camry sedan 2023";
    size_t pos = vehicleInfo.find("camry");
    if (pos != std::string::npos) {
        std::cout << "Found 'camry' at position: " << pos << std::endl;
    }
    
    // Замена подстрок
    std::string oldDesc = "Old wheels 16 inch";
    std::string newDesc = oldDesc;
    size_t replacePos = newDesc.find("Old");
    if (replacePos != std::string::npos) {
        newDesc.replace(replacePos, 3, "New");
    }
    std::cout << "Replacement: " << oldDesc << " -> " << newDesc << std::endl;
    
    // Извлечение подстрок
    std::string boltPattern = "5x114.3";
    size_t xPos = boltPattern.find('x');
    if (xPos != std::string::npos) {
        std::string boltCount = boltPattern.substr(0, xPos);
        std::cout << "Number of bolts: " << boltCount << std::endl;
    }
    
    // Дополнительные операции
    std::string partNumber = "ENG-001-V6-TURBO";
    std::cout << "Part number length: " << partNumber.length() << " characters" << std::endl;
    
    // Разделение строки по дефисам
    size_t start = 0;
    size_t end = partNumber.find('-');
    std::cout << "Part number parts: ";
    while (end != std::string::npos) {
        std::cout << partNumber.substr(start, end - start) << " ";
        start = end + 1;
        end = partNumber.find('-', start);
    }
    std::cout << partNumber.substr(start) << std::endl;
}