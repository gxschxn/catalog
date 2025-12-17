#include "userinterface.hpp"
#include <cstdlib>
#include <algorithm>
#include <cmath>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

UserInterface::UserInterface() : app(std::make_unique<AutoPartsApp>()), running(true) {
    initializeTestData();
}

void UserInterface::clearScreen() const {
    std::system(CLEAR_SCREEN);
}

void UserInterface::waitForEnter() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int UserInterface::getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        } else {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error! Enter a number from " << min << " to " << max << "\n";
    }
}

double UserInterface::getDoubleInput(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        } else {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error! Enter a number from " << min << " to " << max << "\n";
    }
}

std::string UserInterface::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void UserInterface::initializeTestData() {
    // Add test data WITHOUT "Engine"/"Wheel" in names
    app->addEnginePart("ENG001", "Toyota", "V6", 350000, "V6");
    app->addEnginePart("ENG002", "Subaru", "EJ20", 280000, "EJ20");
    app->addEnginePart("ENG003", "BMW", "V8", 550000, "V8");
    app->addEnginePart("ENG004", "Honda", "L4", 180000, "L4");
    app->addEnginePart("ENG005", "Ferrari", "V12", 2500000, "V12");
    app->addEnginePart("ENG006", "Toyota", "2JZ", 420000, "L6");
    app->addEnginePart("ENG007", "BMW", "N55", 320000, "L6");
    
    app->addWheelPart("WHE001", "BBS", "Alloy 17\"", 45000, 17.0, "5x114.3");
    app->addWheelPart("WHE002", "OZ", "Forged 18\"", 85000, 18.0, "5x100");
    app->addWheelPart("WHE003", "Ronal", "Steel", 25000, 16.0, "4x100");
    app->addWheelPart("WHE004", "Enkei", "Sport", 120000, 19.0, "5x112");
    app->addWheelPart("WHE005", "Fuel", "Off-road", 95000, 20.0, "6x139.7");
    app->addWheelPart("WHE006", "Audi", "OEM", 65000, 18.0, "5x112");
    app->addWheelPart("WHE007", "Mercedes", "AMG", 150000, 19.0, "5x112");
    app->addWheelPart("WHE008", "BBS", "Premium", 180000, 19.0, "5x120");
    app->addWheelPart("WHE009", "Enkei", "Performance", 95000, 18.0, "5x114.3");
    
    // Set quantities
    auto& catalog = app->getCatalog();
    auto setQty = [&catalog](const std::string& id, int qty) {
        auto part = catalog.findPartById(id);
        if (part) part->setQuantity(qty);
    };
    
    setQty("ENG001", 5);
    setQty("ENG002", 2);
    setQty("ENG003", 0);
    setQty("ENG004", 3);
    setQty("ENG005", 1);
    setQty("ENG006", 4);
    setQty("ENG007", 2);
    
    setQty("WHE001", 10);
    setQty("WHE002", 0);
    setQty("WHE003", 8);
    setQty("WHE004", 3);
    setQty("WHE005", 5);
    setQty("WHE006", 4);
    setQty("WHE007", 2);
    setQty("WHE008", 6);
    setQty("WHE009", 7);
}

// Helper function to center text in a column
std::string centerText(const std::string& text, int width) {
    if (text.length() >= width) return text.substr(0, width);
    
    int padding = width - text.length();
    int leftPadding = padding / 2;
    int rightPadding = padding - leftPadding;
    
    return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
}

// Helper function to format price with spaces as thousand separators
std::string formatPrice(double price) {
    std::string priceStr = std::to_string(static_cast<int>(price));
    
    // Add spaces as thousand separators
    int len = priceStr.length();
    std::string result;
    for (int i = 0; i < len; i++) {
        if (i > 0 && (len - i) % 3 == 0) {
            result += " ";
        }
        result += priceStr[i];
    }
    
    return result + " RUB";
}

void UserInterface::displayPart(const std::shared_ptr<AutoPart>& part, int index) const {
    if (!part) return;
    
    // Column widths for better alignment
    const int col1 = 6;    // No.
    const int col2 = 10;   // ID
    const int col3 = 12;   // Brand
    const int col4 = 20;   // Name
    const int col5 = 18;   // Price
    const int col6 = 12;   // Type
    const int col7 = 10;   // Qty
    const int col8 = 14;   // Status
    
    // No. - центрируем
    std::string noStr = (index >= 0) ? std::to_string(index + 1) + "." : "";
    std::cout << std::right << std::setw(col1) << centerText(noStr, col1 - 1);
    
    // ID - центрируем
    std::string id = part->getId();
    std::cout << std::setw(col2) << centerText(id, col2 - 1);
    
    // Brand - центрируем
    std::string brand = part->getBrand();
    if (brand.length() > col3 - 2) brand = brand.substr(0, col3 - 3) + ".";
    std::cout << std::setw(col3) << centerText(brand, col3 - 1);
    
    // Name - ЦЕНТРИРУЕМ (исправлено)
    std::string name = part->getName();
    if (name.length() > col4 - 2) name = name.substr(0, col4 - 3) + ".";
    std::cout << std::setw(col4) << centerText(name, col4 - 1);
    
    // Price - центрируем с пробелами
    std::string price = formatPrice(part->getPrice());
    std::cout << std::setw(col5) << centerText(price, col5 - 1);
    
    // Type - центрируем
    std::string type = part->getType();
    size_t pos = type.find(":");
    if (pos != std::string::npos) {
        type = type.substr(0, pos);
    }
    std::cout << std::setw(col6) << centerText(type, col6 - 1);
    
    // Quantity - центрируем
    std::string qty = std::to_string(part->getAvailableQuantity());
    std::cout << std::right << std::setw(col7) << centerText(qty, col7 - 1);
    
    // Status - делаем короче и центрируем
    std::string status = part->isAvailable() ? "✓ In stock" : "✗ Out of stock";
    // Если не помещается, делаем еще короче
    if (status.length() > col8 - 2) {
        status = part->isAvailable() ? "✓ Stock" : "✗ No stock";
    }
    std::cout << std::setw(col8) << centerText(status, col8 - 1);
    
    std::cout << std::endl;
}

void UserInterface::displayParts(const std::vector<std::shared_ptr<AutoPart>>& parts) const {
    if (parts.empty()) {
        std::cout << "No parts found.\n";
        return;
    }
    
    // Column widths
    const int col1 = 6;    // No.
    const int col2 = 10;   // ID
    const int col3 = 12;   // Brand
    const int col4 = 20;   // Name
    const int col5 = 18;   // Price
    const int col6 = 12;   // Type
    const int col7 = 10;   // Qty
    const int col8 = 14;   // Status
    
    const int totalWidth = col1 + col2 + col3 + col4 + col5 + col6 + col7 + col8 + 7;
    
    std::cout << "\n" << std::string(totalWidth, '=') << "\n";
    
    // Headers - все центрируем
    std::cout << std::setw(col1) << centerText("No.", col1 - 1)
              << std::setw(col2) << centerText("ID", col2 - 1)
              << std::setw(col3) << centerText("Brand", col3 - 1)
              << std::setw(col4) << centerText("Name", col4 - 1)  // Заголовок тоже по центру
              << std::setw(col5) << centerText("Price", col5 - 1)
              << std::setw(col6) << centerText("Type", col6 - 1)
              << std::setw(col7) << centerText("Qty", col7 - 1)
              << std::setw(col8) << centerText("Status", col8 - 1)
              << std::endl;
    
    std::cout << std::string(totalWidth, '-') << "\n";
    
    // Data
    for (size_t i = 0; i < parts.size(); ++i) {
        displayPart(parts[i], i);
    }
    
    std::cout << std::string(totalWidth, '=') << "\n";
}

void UserInterface::run() {
    showMainMenu();
}

void UserInterface::showMainMenu() {
    while (running) {
        clearScreen();
        
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "   AUTO PARTS CATALOG\n";
        std::cout << "      MAIN MENU\n";
        std::cout << std::string(50, '=') << "\n\n";
        
        std::cout << "1. View Catalog\n";
        std::cout << "2. Search Parts\n";
        std::cout << "3. Advanced Search\n";
        std::cout << "4. Shopping Cart\n";
        std::cout << "5. Checkout\n";
        std::cout << "6. Exit\n";
        
        std::cout << "\n" << std::string(50, '-') << "\n";
        
        int choice = getIntInput("Select action (1-6): ", 1, 6);
        
        switch (choice) {
            case 1:
                viewCatalog();
                break;
            case 2:
                searchParts();
                break;
            case 3:
                searchByMultipleCriteria();
                break;
            case 4:
                manageCart();
                break;
            case 5:
                checkoutOrder();
                break;
            case 6:
                running = false;
                std::cout << "\nExiting program...\n";
                break;
        }
    }
}

void UserInterface::viewCatalog() {
    auto& catalog = app->getCatalog();
    
    while (true) {
        clearScreen();
        
        auto allParts = catalog.getAllParts();
        
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "   FULL PARTS CATALOG\n";
        std::cout << "   Total: " << allParts.size() << " parts\n";
        std::cout << std::string(50, '=') << "\n";
        
        displayParts(allParts);
        
        std::cout << "\nOptions:\n";
        std::cout << "1. Add part to cart (select by number)\n";  // Изменили
        std::cout << "2. Sort by price (ascending)\n";
        std::cout << "3. Sort by price (descending)\n";
        std::cout << "4. Sort by name\n";
        std::cout << "5. Return to main menu\n";
        
        int choice = getIntInput("\nSelect option (1-5): ", 1, 5);
        
        switch (choice) {
            case 1: {
                if (!allParts.empty()) {
                    int partNumber = getIntInput("Enter part number from list: ", 1, allParts.size());
                    auto part = allParts[partNumber - 1];
                    
                    if (!part->isAvailable()) {
                        std::cout << "\nThis part is not available!\n";
                    } else {
                        int availableQty = part->getAvailableQuantity();
                        std::cout << "Available quantity: " << availableQty << "\n";
                        int quantity = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                        app->addToCart(part->getId(), quantity);
                        std::cout << "\nAdded to cart!\n";
                    }
                } else {
                    std::cout << "\nCatalog is empty!\n";
                }
                waitForEnter();
                break;
            }
            case 2: {
                auto sorted = catalog.getSortedByPrice(true);
                clearScreen();
                std::cout << "\nParts sorted by price (ascending):\n";
                displayParts(sorted);
                
                // Добавляем возможность добавления в корзину сразу после сортировки
                if (!sorted.empty()) {
                    std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
                    int addChoice = getIntInput("", 1, 2);
                    if (addChoice == 1) {
                        int partNumber = getIntInput("Enter part number from list: ", 1, sorted.size());
                        auto part = sorted[partNumber - 1];
                        
                        if (!part->isAvailable()) {
                            std::cout << "\nThis part is not available!\n";
                        } else {
                            int availableQty = part->getAvailableQuantity();
                            std::cout << "Available quantity: " << availableQty << "\n";
                            int quantity = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                            app->addToCart(part->getId(), quantity);
                            std::cout << "\nAdded to cart!\n";
                        }
                    }
                }
                waitForEnter();
                break;
            }
            case 3: {
                auto sorted = catalog.getSortedByPrice(false);
                clearScreen();
                std::cout << "\nParts sorted by price (descending):\n";
                displayParts(sorted);
                
                if (!sorted.empty()) {
                    std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
                    int addChoice = getIntInput("", 1, 2);
                    if (addChoice == 1) {
                        int partNumber = getIntInput("Enter part number from list: ", 1, sorted.size());
                        auto part = sorted[partNumber - 1];
                        
                        if (!part->isAvailable()) {
                            std::cout << "\nThis part is not available!\n";
                        } else {
                            int availableQty = part->getAvailableQuantity();
                            std::cout << "Available quantity: " << availableQty << "\n";
                            int quantity = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                            app->addToCart(part->getId(), quantity);
                            std::cout << "\nAdded to cart!\n";
                        }
                    }
                }
                waitForEnter();
                break;
            }
            case 4: {
                auto allPartsCopy = catalog.getAllParts();
                std::sort(allPartsCopy.begin(), allPartsCopy.end(),
                    [](const std::shared_ptr<AutoPart>& a, const std::shared_ptr<AutoPart>& b) {
                        return a->getFullName() < b->getFullName();
                    });
                clearScreen();
                std::cout << "\nParts sorted by name:\n";
                displayParts(allPartsCopy);
                
                if (!allPartsCopy.empty()) {
                    std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
                    int addChoice = getIntInput("", 1, 2);
                    if (addChoice == 1) {
                        int partNumber = getIntInput("Enter part number from list: ", 1, allPartsCopy.size());
                        auto part = allPartsCopy[partNumber - 1];
                        
                        if (!part->isAvailable()) {
                            std::cout << "\nThis part is not available!\n";
                        } else {
                            int availableQty = part->getAvailableQuantity();
                            std::cout << "Available quantity: " << availableQty << "\n";
                            int quantity = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                            app->addToCart(part->getId(), quantity);
                            std::cout << "\nAdded to cart!\n";
                        }
                    }
                }
                waitForEnter();
                break;
            }
            case 5:
                return;
        }
    }
}

void UserInterface::searchParts() {
    auto& catalog = app->getCatalog();
    
    while (true) {
        clearScreen();
        
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "   SEARCH PARTS\n";
        std::cout << std::string(50, '=') << "\n";
        
        std::cout << "Search by:\n";
        std::cout << "1. Part ID\n";
        std::cout << "2. Name/Brand\n";
        std::cout << "3. Vehicle compatibility\n";
        std::cout << "4. Price range\n";
        std::cout << "5. Return to main menu\n";
        
        int choice = getIntInput("\nSelect option (1-5): ", 1, 5);
        
        if (choice == 5) return;
        
        clearScreen();
        
        switch (choice) {
            case 1: {
                std::cout << "\nSEARCH BY ID\n";
                std::cout << std::string(30, '=') << "\n";
                std::string partId = getStringInput("Enter part ID: ");
                
                auto part = catalog.findPartById(partId);
                
                if (part) {
                    std::cout << "\n" << std::string(50, '=') << "\n";
                    std::cout << "PART FOUND:\n";
                    std::vector<std::shared_ptr<AutoPart>> singlePart = {part};
                    displayParts(singlePart);
                    
                    if (part->isAvailable()) {
                        std::cout << "\nAdd to cart? (1-Yes, 2-No): ";
                        int addChoice = getIntInput("", 1, 2);
                        if (addChoice == 1) {
                            int availableQty = part->getAvailableQuantity();
                            std::cout << "Available quantity: " << availableQty << "\n";
                            int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                            app->addToCart(partId, qty);
                            std::cout << "\nAdded to cart!\n";
                        }
                    } else {
                        std::cout << "\n⚠️  This part is not available!\n";
                    }
                } else {
                    std::cout << "\nPart with ID '" << partId << "' not found.\n";
                }
                break;
            }
            case 2: {
                std::cout << "\nSEARCH BY NAME/BRAND\n";
                std::cout << std::string(30, '=') << "\n";
                std::string query = getStringInput("Enter part name or brand: ");
                
                auto allParts = catalog.getAllParts();
                std::vector<std::shared_ptr<AutoPart>> foundParts;
                
                for (const auto& part : allParts) {
                    if (part->getFullName().find(query) != std::string::npos ||
                        part->getBrand().find(query) != std::string::npos ||
                        part->getName().find(query) != std::string::npos) {
                        foundParts.push_back(part);
                    }
                }
                
                std::cout << "\n" << std::string(50, '=') << "\n";
                std::cout << "FOUND " << foundParts.size() << " PARTS:\n";
                displayParts(foundParts);
                
                if (!foundParts.empty()) {
                    std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
                    int addChoice = getIntInput("", 1, 2);
                    if (addChoice == 1) {
                        int partNumber = getIntInput("Enter part number from list: ", 1, foundParts.size());
                        auto part = foundParts[partNumber - 1];
                        
                        if (!part->isAvailable()) {
                            std::cout << "\nThis part is not available!\n";
                        } else {
                            int availableQty = part->getAvailableQuantity();
                            std::cout << "Available quantity: " << availableQty << "\n";
                            int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                            app->addToCart(part->getId(), qty);
                            std::cout << "\nAdded to cart!\n";
                        }
                    }
                }
                break;
            }
            case 3: {
                std::cout << "\nSEARCH BY COMPATIBILITY\n";
                std::cout << std::string(30, '=') << "\n";
                std::string vehicle = getStringInput("Enter vehicle model: ");
                
                auto compatibleParts = app->findForVehicle(vehicle);
                
                std::cout << "\n" << std::string(50, '=') << "\n";
                std::cout << "PARTS FOR " << vehicle << ":\n";
                displayParts(compatibleParts);
                
                if (!compatibleParts.empty()) {
                    // Filter only available parts
                    std::vector<std::shared_ptr<AutoPart>> availableParts;
                    for (const auto& part : compatibleParts) {
                        if (part->isAvailable()) {
                            availableParts.push_back(part);
                        }
                    }
                    
                    if (!availableParts.empty()) {
                        std::cout << "\nAvailable parts:\n";
                        for (size_t i = 0; i < availableParts.size(); ++i) {
                            std::cout << i + 1 << ". " << availableParts[i]->getFullName() 
                                     << " (" << availableParts[i]->getPrice() << " RUB) - Qty: "
                                     << availableParts[i]->getAvailableQuantity() << "\n";
                        }
                        
                        std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
                        int addChoice = getIntInput("", 1, 2);
                        if (addChoice == 1) {
                            int partNumber = getIntInput("Enter part number from list: ", 1, availableParts.size());
                            auto part = availableParts[partNumber - 1];
                            
                            int availableQty = part->getAvailableQuantity();
                            std::cout << "Available quantity: " << availableQty << "\n";
                            int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                            app->addToCart(part->getId(), qty);
                            std::cout << "\nAdded to cart!\n";
                        }
                    } else {
                        std::cout << "\n⚠️  No parts available for this model.\n";
                    }
                }
                break;
            }
            case 4: {
                searchByPriceRange();
                break;
            }
        }
        
        waitForEnter();
    }
}

void UserInterface::searchByPriceRange() {
    auto& catalog = app->getCatalog();
    
    std::cout << "\nSEARCH BY PRICE RANGE\n";
    std::cout << std::string(30, '=') << "\n";
    
    double minPrice = getDoubleInput("Minimum price (0 for no limit): ", 0);
    double maxPrice = getDoubleInput("Maximum price (0 for no limit): ", 0);
    
    // If both are 0, no limits
    if (minPrice == 0 && maxPrice == 0) {
        std::cout << "\nNo price limits applied.\n";
        auto allParts = catalog.getAllParts();
        displayParts(allParts);
        
        if (!allParts.empty()) {
            std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
            int addChoice = getIntInput("", 1, 2);
            if (addChoice == 1) {
                int partNumber = getIntInput("Enter part number from list: ", 1, allParts.size());
                auto part = allParts[partNumber - 1];
                
                if (!part->isAvailable()) {
                    std::cout << "\nThis part is not available!\n";
                } else {
                    int availableQty = part->getAvailableQuantity();
                    std::cout << "Available quantity: " << availableQty << "\n";
                    int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                    app->addToCart(part->getId(), qty);
                    std::cout << "\nAdded to cart!\n";
                }
            }
        }
        return;
    }
    
    // If maxPrice is 0, set to max value
    if (maxPrice == 0) maxPrice = std::numeric_limits<double>::max();
    
    // Swap if min > max
    if (minPrice > maxPrice) {
        std::swap(minPrice, maxPrice);
    }
    
    auto allParts = catalog.getAllParts();
    std::vector<std::shared_ptr<AutoPart>> filteredParts;
    
    for (const auto& part : allParts) {
        double price = part->getPrice();
        if (price >= minPrice && price <= maxPrice) {
            filteredParts.push_back(part);
        }
    }
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::string maxStr = (maxPrice == std::numeric_limits<double>::max()) ? "∞" : formatPrice(maxPrice);
    std::cout << "PARTS IN PRICE RANGE " << formatPrice(minPrice) << " - " << maxStr << ":\n";
    displayParts(filteredParts);
    
    if (!filteredParts.empty()) {
        std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
        int addChoice = getIntInput("", 1, 2);
        if (addChoice == 1) {
            int partNumber = getIntInput("Enter part number from list: ", 1, filteredParts.size());
            auto part = filteredParts[partNumber - 1];
            
            if (!part->isAvailable()) {
                std::cout << "\nThis part is not available!\n";
            } else {
                int availableQty = part->getAvailableQuantity();
                std::cout << "Available quantity: " << availableQty << "\n";
                int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                app->addToCart(part->getId(), qty);
                std::cout << "\nAdded to cart!\n";
            }
        }
    }
}

void UserInterface::searchByMultipleCriteria() {
    auto& catalog = app->getCatalog();
    
    std::cout << "\nADVANCED SEARCH\n";
    std::cout << std::string(30, '=') << "\n";
    std::cout << "Enter search criteria (press Enter to skip any field):\n\n";
    
    // Collect criteria
    std::string brand = getStringInput("Brand: ");
    std::string nameKeyword = getStringInput("Name contains: ");
    
    double minPrice = 0, maxPrice = 0;
    std::string priceInput;
    
    priceInput = getStringInput("Minimum price (empty for no limit): ");
    if (!priceInput.empty()) {
        try { minPrice = std::stod(priceInput); } catch (...) { minPrice = 0; }
    }
    
    priceInput = getStringInput("Maximum price (empty for no limit): ");
    if (!priceInput.empty()) {
        try { maxPrice = std::stod(priceInput); } catch (...) { maxPrice = 0; }
    }
    
    // Part type
    std::cout << "\nPart type:\n";
    std::cout << "1. Any type\n";
    std::cout << "2. Engines only\n";
    std::cout << "3. Wheels only\n";
    int typeChoice = getIntInput("Select (1-3): ", 1, 3);
    std::string partType = "";
    if (typeChoice == 2) partType = "Engine";
    else if (typeChoice == 3) partType = "Wheel";
    
    // Availability
    std::cout << "\nAvailability:\n";
    std::cout << "1. Available only\n";
    std::cout << "2. All parts\n";
    int availChoice = getIntInput("Select (1-2): ", 1, 2);
    bool inStockOnly = (availChoice == 1);
    
    // Perform search
    auto allParts = catalog.getAllParts();
    std::vector<std::shared_ptr<AutoPart>> filteredParts;
    
    for (const auto& part : allParts) {
        bool matches = true;
        
        // Brand filter
        if (!brand.empty() && part->getBrand().find(brand) == std::string::npos) {
            matches = false;
        }
        
        // Name filter
        if (!nameKeyword.empty() && part->getName().find(nameKeyword) == std::string::npos) {
            matches = false;
        }
        
        // Price filter
        double price = part->getPrice();
        if (minPrice > 0 && price < minPrice) matches = false;
        if (maxPrice > 0 && price > maxPrice) matches = false;
        
        // Type filter
        if (!partType.empty() && part->getType().find(partType) == std::string::npos) {
            matches = false;
        }
        
        // Availability filter
        if (inStockOnly && !part->isAvailable()) {
            matches = false;
        }
        
        if (matches) {
            filteredParts.push_back(part);
        }
    }
    
    // Display results
    clearScreen();
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "ADVANCED SEARCH RESULTS\n";
    
    // Show applied filters
    std::cout << "Applied filters:\n";
    std::cout << std::string(30, '-') << "\n";
    if (!brand.empty()) std::cout << "  Brand: " << brand << "\n";
    if (!nameKeyword.empty()) std::cout << "  Name contains: " << nameKeyword << "\n";
    if (minPrice > 0) std::cout << "  Min price: " << formatPrice(minPrice) << "\n";
    if (maxPrice > 0) std::cout << "  Max price: " << formatPrice(maxPrice) << "\n";
    if (!partType.empty()) std::cout << "  Type: " << partType << "\n";
    if (inStockOnly) std::cout << "  Available only: Yes\n";
    std::cout << std::string(30, '-') << "\n";
    
    std::cout << "\nFound " << filteredParts.size() << " parts:\n";
    displayParts(filteredParts);
    
    if (!filteredParts.empty()) {
        std::cout << "\nAdd part to cart? (1-Yes, 2-No): ";
        int addChoice = getIntInput("", 1, 2);
        if (addChoice == 1) {
            int partNumber = getIntInput("Enter part number from list: ", 1, filteredParts.size());
            auto part = filteredParts[partNumber - 1];
            
            if (!part->isAvailable()) {
                std::cout << "\nThis part is not available!\n";
            } else {
                int availableQty = part->getAvailableQuantity();
                std::cout << "Available quantity: " << availableQty << "\n";
                int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                app->addToCart(part->getId(), qty);
                std::cout << "\nAdded to cart!\n";
            }
        }
    }
}

void UserInterface::manageCart() {
    auto& cart = app->getCart();
    auto& catalog = app->getCatalog();
    
    while (true) {
        clearScreen();
        
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "   SHOPPING CART\n";
        std::cout << std::string(50, '=') << "\n\n";
        
        if (cart.getItemCount() == 0) {
            std::cout << "Cart is empty.\n";
        } else {
            std::cout << cart << "\n";
        }
        
        std::cout << "\n" << std::string(30, '-') << "\n";
        std::cout << "Options:\n";
        std::cout << "1. Add part to cart\n";
        std::cout << "2. Remove part from cart\n";
        std::cout << "3. Clear cart\n";
        std::cout << "4. Show operation history\n";
        std::cout << "5. Return to main menu\n";
        
        int choice = getIntInput("\nSelect option (1-5): ", 1, 5);
        
        switch (choice) {
            case 1: {
                std::string partId = getStringInput("Enter part ID: ");
                auto part = catalog.findPartById(partId);
                
                if (!part) {
                    std::cout << "\nPart with this ID not found!\n";
                } else if (!part->isAvailable()) {
                    std::cout << "\nThis part is not available!\n";
                } else {
                    int availableQty = part->getAvailableQuantity();
                    std::cout << "Available quantity: " << availableQty << "\n";
                    int qty = getIntInput("Enter quantity (1-" + std::to_string(availableQty) + "): ", 1, availableQty);
                    app->addToCart(partId, qty);
                    std::cout << "\nAdded to cart!\n";
                }
                waitForEnter();
                break;
            }
            case 2: {
                if (cart.getItemCount() == 0) {
                    std::cout << "\nCart is empty!\n";
                } else {
                    std::string partId = getStringInput("Enter part ID to remove: ");
                    auto part = catalog.findPartById(partId);
                    if (part) {
                        cart.removeItem(part);
                        std::cout << "\nRemoved from cart!\n";
                    } else {
                        std::cout << "\nPart not found in cart.\n";
                    }
                }
                waitForEnter();
                break;
            }
            case 3: {
                cart.clear();
                std::cout << "\nCart cleared!\n";
                waitForEnter();
                break;
            }
            case 4: {
                auto history = cart.getOperationHistory();
                if (history.empty()) {
                    std::cout << "\nOperation history is empty.\n";
                } else {
                    std::cout << "\nCart operation history:\n";
                    std::cout << std::string(40, '-') << "\n";
                    for (const auto& op : history) {
                        std::cout << "• " << op << "\n";
                    }
                }
                waitForEnter();
                break;
            }
            case 5:
                return;
        }
    }
}

void UserInterface::checkoutOrder() {
    auto& cart = app->getCart();
    
    if (cart.getItemCount() == 0) {
        std::cout << "\nCart is empty. Nothing to checkout.\n";
        waitForEnter();
        return;
    }
    
    clearScreen();
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "   CHECKOUT\n";
    std::cout << std::string(50, '=') << "\n\n";
    
    std::cout << cart << "\n\n";
    
    std::cout << "Confirm checkout?\n";
    std::cout << "1. Yes, proceed to checkout\n";
    std::cout << "2. No, return\n";
    
    int choice = getIntInput("\nSelect (1-2): ", 1, 2);
    
    if (choice == 1) {
        clearScreen();
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "   RECEIPT\n";
        std::cout << std::string(50, '=') << "\n\n";
        app->checkout();
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "\nOrder successfully placed!\n";
    }
    
    waitForEnter();
}