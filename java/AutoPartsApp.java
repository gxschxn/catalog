import java.util.List;

public class AutoPartsApp {
    private Catalog catalog;
    private Cart cart;

    public AutoPartsApp() {
        this.catalog = new Catalog();
        this.cart = new Cart();
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
            return this.catalog.findCompatible(vehicle);
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
                         ", Всего создано запчастей: " + AutoPart.getTotalPartsCreated());
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