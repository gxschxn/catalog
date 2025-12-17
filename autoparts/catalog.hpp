#pragma once

#include "autopart.hpp"
#include "enginepart.hpp"
#include "wheel.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>

class Catalog {
private:
    std::unordered_map<std::string, std::unique_ptr<AutoPart>> parts;
    std::unordered_map<std::string, AutoPart*> partsById;  // Новая мапа для поиска по ID
    std::list<std::string> recentAdditions;
    static const size_t maxRecentItems = 10;
    
public:
    Catalog() = default;
    
    // Конструктор перемещения
    Catalog(Catalog&& other) noexcept = default;
    Catalog& operator=(Catalog&& other) noexcept = default;
    
    // Запрещаем копирование
    Catalog(const Catalog&) = delete;
    Catalog& operator=(const Catalog&) = delete;
    
    void addPart(std::unique_ptr<AutoPart> part);
    std::shared_ptr<AutoPart> findPart(const std::string& name);
    std::shared_ptr<AutoPart> findPartById(const std::string& id);  // Новый метод
    std::vector<std::shared_ptr<AutoPart>> findCompatible(const std::string& vehicle);
    
    // Методы с использованием алгоритмов STL
    std::vector<std::shared_ptr<AutoPart>> getAllParts() const;
    std::vector<std::shared_ptr<AutoPart>> getSortedByPrice(bool ascending = true) const;
    std::shared_ptr<AutoPart> findMostExpensive() const;
    bool hasExpensiveParts(double threshold) const;
    
    size_t getSize() const;
    
    std::shared_ptr<AutoPart> operator[](const std::string& partName);
    
    const std::list<std::string>& getRecentAdditions() const;
    
    // Метод для демонстрации шаблонов
    template<typename T>
    std::vector<std::shared_ptr<T>> getPartsOfType() const;
};