#include <iostream>
#include "autopartsapp.hpp"
#include <memory>
#include <algorithm>

using namespace std;

int main() {
    AutoPartsApp app;
    
    cout << "=== АВТОЗАПЧАСТИ: УПРАВЛЕНИЕ МАГАЗИНОМ ===" << endl;
    
    // 1. Добавляем детали в каталог
    cout << "\n1. ПОПОЛНЕНИЕ КАТАЛОГА:" << endl;
    
    app.addEnginePart("ENG001", "V6 Двигатель", 350000, "V6");
    app.addEnginePart("ENG002", "EJ204 Двигатель", 150000, "EJ204");
    app.addEnginePart("ENG003", "V12 Двигатель", 2500000, "V12");
    app.addEnginePart("ENG004", "L4 Двигатель", 120000, "L4");
    
    app.addWheelPart("WHE001", "Литые диски", 80000, 17.0, "5x114.3");
    app.addWheelPart("WHE002", "Кованые диски", 120000, 18.0, "5x100");
    app.addWheelPart("WHE003", "Штампованные диски", 50000, 16.0, "4x100");
    app.addWheelPart("WHE004", "Спортивные диски", 180000, 19.0, "5x112");
    
    app.showStats();
    
    // 2. Демонстрация поиска
    cout << "\n2. ПОИСК ДЕТАЛЕЙ:" << endl;
    
    cout << "Для Toyota Camry:" << endl;
    auto forToyota = app.findForVehicle("toyota camry");
    cout << "  Найдено: " << forToyota.size() << " деталей" << endl;
    
    cout << "\nДля Subaru Impreza:" << endl;
    auto forSubaru = app.findForVehicle("subaru impreza");
    cout << "  Найдено: " << forSubaru.size() << " деталей" << endl;
    
    // 3. Работа с корзиной
    cout << "\n3. РАБОТА С КОРЗИНОЙ:" << endl;
    
    app.addToCart("ENG001", 1);  // V6 Двигатель
    app.addToCart("WHE001", 4);  // Литые диски (4 шт)
    app.addToCart("ENG004", 1);  // L4 Двигатель
    app.addToCart("WHE003", 2);  // Штампованные диски (2 шт)
    
    cout << "Содержимое корзины:" << endl;
    cout << app.getCart() << endl;
    
    // 4. Демонстрация шаблонной функции
    cout << "\n4. ДЕМОНСТРАЦИЯ ШАБЛОННОЙ ФУНКЦИИ:" << endl;
    
    double price = 100000.0;
    double discounted = calculateDiscountedPrice(price, 15.0);
    cout << "Цена: " << price << " руб." << endl;
    cout << "Цена со скидкой 15%: " << discounted << " руб." << endl;
    
    // 5. Демонстрация шаблонного класса
    cout << "\n5. ДЕМОНСТРАЦИЯ ШАБЛОННОГО КЛАССА:" << endl;
    app.demonstratePartInventory();
    
    // 6. Оформление заказа
    cout << "\n6. ОФОРМЛЕНИЕ ЗАКАЗА:" << endl;
    app.checkout();
    
    // 7. Дополнительные операции с контейнерами
    cout << "\n7. ДОПОЛНИТЕЛЬНЫЕ ОПЕРАЦИИ:" << endl;
    
    // Проверяем наличие дорогих деталей через getCatalog()
    auto& catalog = app.getCatalog();
    cout << "Всего деталей в каталоге: " << catalog.getSize() << endl;
    
    // Получаем все детали и сортируем их вручную
    auto allParts = catalog.getAllParts();
    if (!allParts.empty()) {
        cout << "\nВсе детали в каталоге:" << endl;
        for (const auto& part : allParts) {
            cout << "  " << part->getPrice() << " руб. - " 
                 << part->getName() << " (" << part->getType() << ")" << endl;
        }
        
        // Сортируем по цене (по возрастанию) - используем алгоритм sort
        sort(allParts.begin(), allParts.end(),
            [](const shared_ptr<AutoPart>& a, const shared_ptr<AutoPart>& b) {
                return a->getPrice() < b->getPrice();
            });
        
        cout << "\nДетали, отсортированные по цене (по возрастанию):" << endl;
        for (const auto& part : allParts) {
            cout << "  " << part->getPrice() << " руб. - " << part->getName() << endl;
        }
        
        // Проверяем наличие дорогих деталей
        bool hasExpensive = catalog.hasExpensiveParts(1000000);
        cout << "\nЕсть детали дороже 1 млн руб.: " << (hasExpensive ? "Да" : "Нет") << endl;
        
        // Ищем самую дорогую деталь
        auto mostExpensive = catalog.findMostExpensive();
        if (mostExpensive) {
            cout << "Самая дорогая деталь: " << mostExpensive->getName() 
                 << " (" << mostExpensive->getPrice() << " руб.)" << endl;
        }
    }
    
    // 8. Демонстрация использования контейнеров в корзине
    cout << "\n8. ОПЕРАЦИИ С КОРЗИНОЙ:" << endl;
    auto& cart = app.getCart();
    
    // Проверяем наличие дорогих товаров в корзине
    bool hasExpensiveItems = cart.hasExpensiveItems(100000);
    cout << "В корзине есть товары дороже 100000 руб.: " 
         << (hasExpensiveItems ? "Да" : "Нет") << endl;
    
    // Получаем отсортированный список товаров из корзины
    auto sortedCartItems = cart.getSortedByPrice(true);
    if (!sortedCartItems.empty()) {
        cout << "Товары в корзине, отсортированные по цене:" << endl;
        for (const auto& item : sortedCartItems) {
            cout << "  " << item->getPrice() << " руб. - " << item->getName() << endl;
        }
    }
    
    // 9. Демонстрация недавно добавленных деталей
    cout << "\n9. НЕДАВНО ДОБАВЛЕННЫЕ ДЕТАЛИ:" << endl;
    auto recent = catalog.getRecentAdditions();
    if (!recent.empty()) {
        cout << "Последние " << recent.size() << " добавленных деталей:" << endl;
        for (const auto& item : recent) {
            cout << "  " << item << endl;
        }
    }
    
    cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;
    
    return 0;
}