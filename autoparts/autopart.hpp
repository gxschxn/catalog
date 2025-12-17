#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <map>
#include <array>

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
    std::string brand;
    std::string name;
    double price;
    int quantity;
    std::vector<std::string> compatibilityList;
    
public:
    AutoPart(std::string id, std::string brand, std::string name, double price);
    virtual ~AutoPart();
    
    // Запрещаем копирование по умолчанию
    AutoPart(const AutoPart& other) = delete;
    
    // Базовые методы
    double getPrice() const;
    bool isAvailable() const;
    std::string getFullInfo() const;
    bool isValid() const;
    
    bool checkCompatibility(const std::string& vehicle) const override;
    std::string getCompatibilityInfo() const override;
    
    virtual std::string getType() const = 0;
    virtual std::string getSpecifications() const = 0;
    
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
    std::string getBrand() const { return brand; }
    std::string getName() const { return name; }
    std::string getFullName() const { return brand + " " + name; }
    int getQuantity() const { return quantity; }
    int getAvailableQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }
    
    static constexpr int MAX_BATCH_SIZE = 100;
    static constexpr double MIN_PRICE = 0.01;
    static constexpr double MAX_PRICE = 10000000.0;
    
    constexpr double calculatePriceWithTax(double taxRate) const {
        return price * (1.0 + taxRate / 100.0);
    }
    
    constexpr bool isPriceInRange(double min, double max) const {
        return price >= min && price <= max;
    }
    
protected:
    void addCompatibility(const std::string& vehicle);
    void setCompatibilityList(const std::vector<std::string>& list);
};

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
calculateDiscountedPrice(T basePrice, double discountPercent) {
    if (basePrice < 0 || discountPercent < 0 || discountPercent > 100) {
        return basePrice;
    }
    return basePrice * (1 - discountPercent / 100);
}

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

constexpr double calculateVAT(double price, double vatRate = 20.0) {
    return price * (vatRate / 100.0);
}

constexpr bool isValidPrice(double price) {
    return price > AutoPart::MIN_PRICE && price < AutoPart::MAX_PRICE;
}

class PriceCalculator {
private:
    double basePrice;
    
public:
    constexpr PriceCalculator(double price) : basePrice(price) {}
    
    // constexpr метод
    constexpr double getPriceWithDiscount(double discount) const {
        return basePrice * (1.0 - discount / 100.0);
    }
    
    constexpr double getPriceWithVAT(double vatRate = 20.0) const {
        return basePrice * (1.0 + vatRate / 100.0);
    }
    
    constexpr bool isExpensive(double threshold = 100000.0) const {
        return basePrice > threshold;
    }
};
