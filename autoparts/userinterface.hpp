#pragma once

#include "autopartsapp.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <sstream>
#include <iomanip>
#include <limits>

class UserInterface {
private:
    std::unique_ptr<AutoPartsApp> app;
    bool running;
    
    // Вспомогательные методы
    void clearScreen() const;
    void waitForEnter() const;
    int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
    double getDoubleInput(const std::string& prompt, double min = -1e9, double max = 1e9);
    std::string getStringInput(const std::string& prompt);
    
    // Методы меню
    void showMainMenu();
    void viewCatalog();
    void searchParts();
    void advancedSearch();  // Новый метод для расширенного поиска
    void filterParts();
    void manageCart();
    void checkoutOrder();
    
    // Вспомогательные методы отображения
    void displayPart(const std::shared_ptr<AutoPart>& part, int index = -1) const;
    void displayParts(const std::vector<std::shared_ptr<AutoPart>>& parts) const;
    
    // Методы для поиска
    void searchByMultipleCriteria();
    void searchByPriceRange();
    
    void initializeTestData();
    
public:
    UserInterface();
    void run();
};