#include <iostream>
#include "autopartsapp.hpp"

using namespace std;

int main() {
    
    AutoPartsApp app;
    
    try {
        // добавление запчасти в каталог
        cout << "\n1. Adding parts to catalog:" << endl;
        app.addEnginePart("ENG001", "V6 Engine", 350000, "V6");
        app.addEnginePart("ENG002", "EJ204 Engine", 150000, "EJ204");
        app.addEnginePart("ENG003", "V12 Engine", 2500000, "V12");
        app.addWheelPart("WHE001", "Alloy Wheels", 80000, 17.0, "5x114.3");
        app.addWheelPart("WHE002", "Forged Wheels", 120000, 18.0, "5x100");
        
        app.showStats();
        
        // демонстрация работы со строками
        app.demonstrateStringOperations();
        
        // поиск подходящих запчастей
        cout << "\n2. Finding parts for Toyota Camry:" << endl;
        auto compatibleParts1 = app.findForVehicle("toyota camry sedan");
        cout << "Found compatible parts: " << compatibleParts1.size() << endl;
        for (const auto& part : compatibleParts1) {
            if (part) {
                cout << "  - " << part->getFullInfo() << " (" << part->getType() << ")" << endl;
            }
        }

        cout << "\n3. Finding parts for Subaru Impreza:" << endl;
        auto compatibleParts2 = app.findForVehicle("subaru impreza");
        cout << "Found compatible parts: " << compatibleParts2.size() << endl;
        for (const auto& part : compatibleParts2) {
            if (part) {
                cout << "  - " << part->getFullInfo() << " (" << part->getType() << ")" << endl;
            }
        }

        cout << "\n4. Finding parts for Ferrari:" << endl;
        auto compatibleParts3 = app.findForVehicle("ferrari 488");
        cout << "Found compatible parts: " << compatibleParts3.size() << endl;
        for (const auto& part : compatibleParts3) {
            if (part) {
                cout << "  - " << part->getFullInfo() << " (" << part->getType() << ")" << endl;
            }
        }
        
        // добавление в корзину
        cout << "\n5. Adding items to cart:" << endl;
        
        app.addToCart("V6 Engine - 350000 руб. (ENG001)");
        app.addToCart("Alloy Wheels - 80000 руб. (WHE001)", 4);
        
        app.showStats();
        
        // оформление заказа
        cout << "\n6. Checkout:" << endl;
        app.checkout();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }
        
    return 0;
}