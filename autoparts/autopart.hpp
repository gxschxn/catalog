#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <map>

// Интерфейс для проверки совместимости
class ICompatibilityCheckable {
public:
    virtual ~ICompatibilityCheckable() = default;
    virtual bool checkCompatibility(const std::string& vehicle) const = 0;
    virtual std::string getCompatibilityInfo() const = 0;
};

// Базовый класс
class AutoPart : public ICompatibilityCheckable {
protected:
    std::string id;
    std::string name;
    double price;
    int quantity;
    std::vector<std::string> compatibilityList;
    
public:
    AutoPart(std::string id, std::string name, double price);
    virtual ~AutoPart();
    
    // Запрещаем копирование по умолчанию
    AutoPart(const AutoPart& other) = delete;
    
    // Базовые методы
    double getPrice() const;
    bool isAvailable() const;
    std::string getFullInfo() const;
    bool isValid() const;
    
    // Реализация интерфейса ICompatibilityCheckable
    bool checkCompatibility(const std::string& vehicle) const override;
    std::string getCompatibilityInfo() const override;
    
    // Чисто виртуальные методы
    virtual std::string getType() const = 0;
    virtual std::string getSpecifications() const = 0;
    
    // Виртуальные методы с реализацией по умолчанию
    virtual void displayInfo() const;
    virtual std::string getDetailedInfo() const;
    
    // Перегрузка операторов
    bool operator==(const AutoPart& other) const;
    bool operator!=(const AutoPart& other) const;
    bool operator<(const AutoPart& other) const;
    bool operator>(const AutoPart& other) const;
    
    AutoPart& operator=(const AutoPart& other);
    
    friend std::ostream& operator<<(std::ostream& os, const AutoPart& part);
    
    // Геттеры
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }
    
protected:
    void addCompatibility(const std::string& vehicle);
    void setCompatibilityList(const std::vector<std::string>& list);
};

// Шаблонная функция для вычисления стоимости со скидкой (без концептов)
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
calculateDiscountedPrice(T basePrice, double discountPercent) {
    if (basePrice < 0 || discountPercent < 0 || discountPercent > 100) {
        return basePrice;
    }
    return basePrice * (1 - discountPercent / 100);
}

// Шаблонный класс инвентаря (без концептов)
template<typename T>
class PartInventory {
    static_assert(std::is_base_of<AutoPart, T>::value, 
                  "T must be derived from AutoPart");
    
private:
    std::vector<T*> parts;
    std::map<std::string, T*> partMap;
    
public:
    PartInventory() = default;
    
    ~PartInventory() {
        for (auto part : parts) {
            delete part;
        }
    }
    
    // Нешаблонные методы
    size_t size() const { return parts.size(); }
    bool empty() const { return parts.empty(); }
    
    // Шаблонный метод для добавления
    template<typename... Args>
    void addPart(Args&&... args) {
        T* newPart = new T(std::forward<Args>(args)...);
        parts.push_back(newPart);
        partMap[newPart->getId()] = newPart;
    }
    
    // Поиск по ID
    T* findById(const std::string& id) const {
        auto it = partMap.find(id);
        return (it != partMap.end()) ? it->second : nullptr;
    }
    
    // Поиск самой дорогой детали
    T* findMostExpensive() const {
        if (parts.empty()) return nullptr;
        
        auto it = std::max_element(parts.begin(), parts.end(),
            [](const T* a, const T* b) {
                return a->getPrice() < b->getPrice();
            });
        return *it;
    }
    
    // Фильтрация по минимальной цене
    std::vector<T*> filterByMinPrice(double minPrice) const {
        std::vector<T*> result;
        
        std::copy_if(parts.begin(), parts.end(), std::back_inserter(result),
            [minPrice](const T* part) {
                return part && part->getPrice() >= minPrice;
            });
        
        return result;
    }
    
    // Получение всех деталей
    const std::vector<T*>& getAllParts() const {
        return parts;
    }
};