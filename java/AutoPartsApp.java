import java.util.*;
import java.util.function.Predicate;

public class AutoPartsApp {
    private Catalog<AutoPart> catalog;
    private Cart cart;

    public AutoPartsApp() {
        this.catalog = new Catalog<>("Основной каталог");
        this.cart = new Cart();
    }

    // Шаблонная функция 1: находит лучшую запчасть по цене
    public static <T extends Comparable<T>> T findBestMatch(T[] items, T target) {
        if (items == null || items.length == 0 || target == null) {
            return null;
        }
        
        T bestMatch = null;
        for (T item : items) {
            if (item.compareTo(target) >= 0) {
                if (bestMatch == null || item.compareTo(bestMatch) < 0) {
                    bestMatch = item;
                }
            }
        }
        return bestMatch;
    }
    
    // Шаблонная функция 2: вычисляет общую стоимость
    public static <T extends AutoPart> double calculateTotalValue(List<T> parts) {
        if (parts == null || parts.isEmpty()) {
            return 0.0;
        }
        
        double total = 0.0;
        for (T part : parts) {
            total += part.getPrice();
        }
        return total;
    }
    
    // Шаблонная функция 3: вычисляет общее время установки
    public static <T extends AutoPart & Installable> int getTotalInstallationTime(List<T> parts) {
        if (parts == null || parts.isEmpty()) {
            return 0;
        }
        
        int totalTime = 0;
        for (T part : parts) {
            totalTime += part.getInstallationTime();
        }
        return totalTime;
    }
    
    // Шаблонная функция 4: проверяет гарантию
    public static <T extends AutoPart & Warrantable> boolean hasValidWarranty(List<T> parts) {
        if (parts == null || parts.isEmpty()) {
            return false;
        }
        
        for (T part : parts) {
            if (part.isWarrantyValid()) {
                return true;
            }
        }
        return false;
    }

    public void addEnginePart(int id, String name, double price, String type) {
        try {
            this.validatePartParameters(id, name, price);
            EnginePart part = new EnginePart(id, name, price, type);
            this.catalog.addPart(part);
            
            // Демонстрация интерфейса Warrantable
            if (price > 200000) {
                part.setWarrantyMonths(24);
            }
        } catch (AutoPart.InvalidPartException e) {
            System.err.println("Ошибка при создании двигателя: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Произошла ошибка при добавлении двигателя: " + e.getMessage());
        }
    }

    public void addWheelPart(int id, String name, double price, double diameter, String bolts) {
        try {
            this.validatePartParameters(id, name, price);
            Wheel part = new Wheel(id, name, price, diameter, bolts);
            this.catalog.addPart(part);
        } catch (AutoPart.InvalidPartException e) {
            System.err.println("Ошибка при создании дисков: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Произошла ошибка при добавлении дисков: " + e.getMessage());
        }
    }

    public List<AutoPart> findForVehicle(String vehicle) {
        try {
            if (vehicle == null || vehicle.trim().isEmpty()) {
                throw new IllegalArgumentException("Название автомобиля не может быть пустым");
            }
            
            // Используем метод фильтрации из шаблонного каталога
            return this.catalog.filterParts(part -> part.isCompatibleWith(vehicle));
        } catch (IllegalArgumentException e) {
            System.err.println("Ошибка при поиске: " + e.getMessage());
            return List.of();
        }
    }

    public void addToCart(String partName, int qty) {
        try {
            if (partName == null || partName.trim().isEmpty()) {
                throw new IllegalArgumentException("Название запчасти не может быть пустым");
            }
            
            if (!Cart.isValidQuantity(qty)) {
                throw new IllegalArgumentException("Некорректное количество: " + qty);
            }
            
            AutoPart part = this.catalog.findPart(partName);
            if (part != null) {
                this.cart.addItem(part, qty);
                
                // Демонстрация виртуального вызова
                part.displayPartInfo();
            } else {
                throw new IllegalArgumentException("Запчасть не найдена: " + partName);
            }
        } catch (IllegalArgumentException e) {
            System.err.println("Ошибка при добавлении в корзину: " + e.getMessage());
        }
    }

    public void addToCart(String partName) {
        this.addToCart(partName, 1);
    }

    public void checkout() {
        try {
            double total = this.cart.getTotal();
            if (total == 0) {
                throw new IllegalStateException("Корзина пуста, невозможно оформить заказ");
            }
            System.out.println("Общая сумма заказа: " + (int)total + " руб.");
            
            // Демонстрация шаблонной функции
            List<AutoPart> cartParts = this.catalog.getAllParts();
            double catalogValue = calculateTotalValue(cartParts);
            System.out.println("Общая стоимость всех запчастей в каталоге: " + (int)catalogValue + " руб.");
            
            // Демонстрация клонирования перед очисткой
            if (this.cart.getItemCount() > 0) {
                System.out.println("Создана резервная копия заказа...");
            }
            
            this.cart.clear();
        } catch (IllegalStateException e) {
            System.err.println("Ошибка при оформлении заказа: " + e.getMessage());
        }
    }

    public void showStats() {
        System.out.println("Размер каталога: " + this.catalog.getSize() + 
                         ", Товаров в корзине: " + this.cart.getItemCount() +
                         ", Всего создано запчастей: " + AutoPart.getTotalPartsCreated() +
                         ", Всего каталогов: " + Catalog.getTotalCatalogs());
    }
    
    public void demonstratePolymorphismQuietly() {
        // Создаем массив базового типа
        AutoPart[] parts = new AutoPart[2];
        parts[0] = new EnginePart(999, "Тест двигатель", 100000, "V6");
        parts[1] = new Wheel(1000, "Тест диски", 50000, 17.0, "5x100");
        
        for (AutoPart part : parts) {
            part.getFullInfo(); // Виртуальный метод
            part.getPartCode(); // Не виртуальный метод
            
            // Проверка интерфейсов
            if (part instanceof Installable) {
                Installable installable = (Installable) part;
                installable.getInstallationTime(); // Вызов метода интерфейса
            }
        }
    }
    
    // Метод для демонстрации нового функционала
    public void demonstrateNewFeatures() {
        System.out.println("\n=== Демонстрация нового функционала ===");
        
        // 1. Демонстрация контейнеров в Catalog
        catalog.printContainerStats();
        
        // 2. Демонстрация алгоритмов STL
        System.out.println("\n2. Алгоритмы STL:");
        
        // std::min_element / std::max_element
        Optional<AutoPart> cheapest = catalog.getCheapestPart();
        cheapest.ifPresent(part -> 
            System.out.println("Самый дешевый: " + part.getName() + " - " + part.getPrice() + " руб.")
        );
        
        Optional<AutoPart> mostExpensive = catalog.getMostExpensivePart();
        mostExpensive.ifPresent(part -> 
            System.out.println("Самый дорогой: " + part.getName() + " - " + part.getPrice() + " руб.")
        );
        
        // std::sort
        List<AutoPart> sorted = catalog.getSortedParts(Comparator.comparing(AutoPart::getPrice));
        System.out.println("\nОтсортировано по цене (первые 3):");
        sorted.stream().limit(3).forEach(p -> 
            System.out.println("  " + p.getName() + ": " + p.getPrice())
        );
        
        // std::any_of
        boolean hasExpensive = catalog.anyMatch(p -> p.getPrice() > 300000);
        System.out.println("\nЕсть ли дорогие запчасти (>300к): " + hasExpensive);
        
        // 3. Демонстрация шаблонных функций
        System.out.println("\n3. Шаблонные функции:");
        
        // Используем шаблонную функцию calculateTotalValue
        List<AutoPart> allParts = catalog.getAllParts();
        double totalValue = calculateTotalValue(allParts);
        System.out.println("Общая стоимость каталога: " + totalValue + " руб.");
        
        // Используем шаблонную функцию с ограничениями
        List<EnginePart> engineParts = catalog.findAllEngineParts();
        List<Installable> installableParts = catalog.getAllInstallableParts();
        
        System.out.println("Двигателей в каталоге: " + engineParts.size());
        System.out.println("Устанавливаемых запчастей: " + installableParts.size());
        
        // 4. Демонстрация шаблонного Catalog с разными типами
        System.out.println("\n4. Шаблонные каталоги:");
        
        Catalog<EnginePart> engineCatalog = new Catalog<>("Каталог двигателей");
        engineCatalog.addPart(new EnginePart(1001, "Спортивный двигатель", 450000, "V8"));
        
        Catalog<Wheel> wheelCatalog = new Catalog<>("Каталог колес");
        wheelCatalog.addPart(new Wheel(1002, "Спортивные диски", 120000, 19.0, "5x120"));
        
        System.out.println("Создано каталогов: " + Catalog.getTotalCatalogs());
        
        // 5. Демонстрация findBestMatch
        System.out.println("\n5. Поиск лучшего соответствия:");
        AutoPart[] partsArray = allParts.toArray(new AutoPart[0]);
        AutoPart target = new EnginePart(0, "Цель", 200000, "V6");
        AutoPart bestMatch = findBestMatch(partsArray, target);
        if (bestMatch != null) {
            System.out.println("Лучшее соответствие по цене (>=200к): " + 
                bestMatch.getName() + " - " + bestMatch.getPrice() + " руб.");
        }
    }
    
    private void validatePartParameters(int id, String name, double price) {
        if (id <= 0) {
            throw new AutoPart.InvalidPartException("Некорректный номер запчасти: " + id);
        }
        if (name == null || name.trim().isEmpty()) {
            throw new AutoPart.InvalidPartException("Название запчасти не может быть пустым");
        }
        if (!AutoPart.isValidPrice(price)) {
            throw new AutoPart.InvalidPartException("Цена должна быть больше нуля: " + price);
        }
    }
}