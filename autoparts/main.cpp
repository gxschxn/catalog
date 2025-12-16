#include <iostream>
#include "autopartsapp.hpp"

using namespace std;

int main() {
    
    AutoPartsApp app;
    
    try {
        cout << "=== Автозапчасти: Магазин ===" << endl;
        
        // добавление запчасти в каталог
        cout << "\n1. Пополнение каталога запчастей:" << endl;
        app.addEnginePart("ENG001", "V6 Двигатель", 350000, "V6");
        app.addEnginePart("ENG002", "EJ204 Двигатель", 150000, "EJ204");
        app.addEnginePart("ENG003", "V12 Двигатель", 2500000, "V12");
        app.addWheelPart("WHE001", "Литые диски", 80000, 17.0, "5x114.3");
        app.addWheelPart("WHE002", "Кованые диски", 120000, 18.0, "5x100");
        app.addWheelPart("WHE003", "Штампованные диски", 50000, 16.0, "4x100");
        app.addEnginePart("ENG004", "L4 Двигатель", 120000, "L4");
        
        app.showStats();
        
        // поиск подходящих запчастей
        cout << "\n2. Подбор запчастей:" << endl;
        
        cout << "Для Toyota Camry:" << endl;
        auto compatibleParts1 = app.findForVehicle("toyota camry sedan");
        cout << "Найдено: " << compatibleParts1.size() << " запчастей" << endl;
        for (const auto& part : compatibleParts1) {
            if (part) {
                cout << "  - " << part->getFullInfo() << endl;
            }
        }

        cout << "\nДля Subaru Impreza:" << endl;
        auto compatibleParts2 = app.findForVehicle("subaru impreza");
        cout << "Найдено: " << compatibleParts2.size() << " запчастей" << endl;
        for (const auto& part : compatibleParts2) {
            if (part) {
                cout << "  - " << part->getFullInfo() << endl;
            }
        }

        cout << "\nДля Ferrari 488:" << endl;
        auto compatibleParts3 = app.findForVehicle("ferrari 488");
        cout << "Найдено: " << compatibleParts3.size() << " запчастей" << endl;
        for (const auto& part : compatibleParts3) {
            if (part) {
                cout << "  - " << part->getFullInfo() << endl;
            }
        }
        
        // добавление в корзину - ВАЖНО: используем тот же формат что и в getFullInfo()
        cout << "\n3. Формирование заказа:" << endl;
        
        cout << "Добавлены в корзину:" << endl;
        
        // Используем формат как в выводе выше: "V6 Двигатель - 350000 RUB (ENG001)"
        cout << "  - V6 Двигатель (1 шт)" << endl;
        app.addToCart("V6 Двигатель - 350000 RUB (ENG001)");  // RUB вместо руб.
        
        cout << "  - Литые диски (4 шт)" << endl;
        app.addToCart("Литые диски - 80000 RUB (WHE001)", 4);  // RUB вместо руб.
        
        cout << "  - EJ204 Двигатель (1 шт)" << endl;
        app.addToCart("EJ204 Двигатель - 150000 RUB (ENG002)");  // RUB вместо руб.
        
        cout << "  - Кованые диски (2 шт)" << endl;
        app.addToCart("Кованые диски - 120000 RUB (WHE002)", 2);  // RUB вместо руб.
        
        app.showStats();
        
        // оформление заказа
        cout << "\n4. Оформление заказа:" << endl;
        app.checkout();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная ошибка" << std::endl;
        return 1;
    }
        
    cout << "\n=== Работа программы завершена ===" << endl;
    return 0;
}