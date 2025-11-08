#include <iostream>
#include "autopartsapp.hpp"

using namespace std;

int main() {
    cout << "=== Демонстрация системы автозапчастей ===" << endl;
    
    AutoPartsApp app;
    
    // добавление запчасти в каталог
    cout << "\n1. Добавляем запчасти в каталог:" << endl;
    app.addEnginePart("ENG001", "Двигатель V6", 350000, "V6");
    app.addEnginePart("ENG002", "Двигатель EJ204", 150000, "EJ204");
    app.addEnginePart("ENG003", "Двигатель V12", 2500000, "V12");
    app.addWheelPart("WHE001", "Литые диски", 80000, 17.0, "5x114.3");
    app.addWheelPart("WHE002", "Кованые диски", 120000, 18.0, "5x100");
    
    app.showStats();
    
    // поиск подходящих запчастей
    cout << "\n2. Поиск запчастей для Toyota Camry:" << endl;
    auto compatibleParts1 = app.findForVehicle("toyota camry sedan");
    cout << "Найдено совместимых запчастей: " << compatibleParts1.size() << endl;

    cout << "\n3. Поиск запчастей для Subaru Impreza:" << endl;
    auto compatibleParts2 = app.findForVehicle("subaru impreza");
    cout << "Найдено совместимых запчастей: " << compatibleParts2.size() << endl;

    cout << "\n4. Поиск запчастей для Ferrari:" << endl;
    auto compatibleParts3 = app.findForVehicle("ferrari 488");
    cout << "Найдено совместимых запчастей: " << compatibleParts3.size() << endl;
    
    // добавление в корзину
    cout << "\n5. Добавляем товары в корзину:" << endl;
    
    app.addToCart("Двигатель V6 - 350000 руб. (ENG001)");
    app.addToCart("Литые диски - 80000 руб. (WHE001)", 4);
    
    app.showStats();
    
    // оформление заказа
    cout << "\n6. Оформление заказа:" << endl;
    app.checkout();
    
    cout << "\n=== Демонстрация завершена ===" << endl;
    
    return 0;
}