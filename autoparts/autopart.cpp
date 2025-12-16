#include "autopart.hpp"
#include <string>

AutoPart::AutoPart(std::string id, std::string name, double price) 
    : id(id), name(name), price(price), quantity(0) {}

// Конструктор копирования
AutoPart::AutoPart(const AutoPart& other)
    : id(other.id), name(other.name), price(other.price), quantity(other.quantity) {}

double AutoPart::getPrice() const { return price; }

bool AutoPart::isAvailable() const { return quantity > 0; }

std::string AutoPart::getFullInfo() const { 
    // Использование методов std::string для конкатенации
    std::string info = name + " - " + std::to_string(static_cast<int>(price)) + " руб. (" + id + ")";
    return info;
}

bool AutoPart::isValid() const { 
    // Использование методов std::string для проверки
    return !id.empty() && price > 0 && !name.empty();
}

// Перегрузка операторов
bool AutoPart::operator==(const AutoPart& other) const {
    return id == other.id && name == other.name && price == other.price;
}

bool AutoPart::operator!=(const AutoPart& other) const {
    return !(*this == other);
}

bool AutoPart::operator<(const AutoPart& other) const {
    // Сравнение по цене, затем по имени
    if (price != other.price) {
        return price < other.price;
    }
    return name < other.name;
}

// Дружественная функция для вывода
std::ostream& operator<<(std::ostream& os, const AutoPart& part) {
    os << part.getFullInfo();
    return os;
}