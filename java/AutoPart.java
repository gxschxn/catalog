interface Installable {
    String getInstallationInstructions();
    int getInstallationTime();
    
    default String getInstallationInfo() {
        return "Установка: " + getInstallationTime() + " мин";
    }
}

interface Warrantable {
    int getWarrantyMonths();
    void setWarrantyMonths(int months);
    
    default boolean isWarrantyValid() {
        return getWarrantyMonths() > 0;
    }
}

public abstract class AutoPart implements Cloneable, Comparable<AutoPart> {
    protected int id; // protected для демонстрации
    protected String name;
    protected double price;
    protected int quantity;
    
    private static int totalPartsCreated = 0;
    private static final double MIN_PRICE = 0.0;
    
    public static class InvalidPartException extends RuntimeException {
        public InvalidPartException(String message) {
            super(message);
        }
    }

    public AutoPart(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.setPrice(price);
        this.quantity = 0;
        totalPartsCreated++;
    }

    public static int getTotalPartsCreated() {
        return totalPartsCreated;
    }
    
    public static boolean isValidPrice(double price) {
        return price > MIN_PRICE;
    }
    
    // Виртуальный метод
    public String getFullInfo() {
        return this.name + " - " + (int)this.price + " руб. (" + this.id + ")";
    }
    
    // Не виртуальный метод (final)
    public final String getPartCode() {
        return "PART-" + this.id;
    }
    
    // Метод с вызовом виртуальной функции
    public void displayPartInfo() {
        System.out.println("Инфо: " + getFullInfo());
    }
    
    // Метод для доступа к protected полю из производных классов
    protected void updateIdWithPrefix(String prefix) {
        this.name = prefix + this.name;
    }
    
    public double getPrice() { 
        return this.price; 
    }
    
    public void setPrice(double price) {
        if (!isValidPrice(price)) {
            throw new InvalidPartException("Цена должна быть больше нуля: " + price);
        }
        this.price = price;
    }
    
    public int getId() { 
        return this.id; 
    }
    
    public void setId(int id) { 
        if (id <= 0) {
            throw new InvalidPartException("Номер запчасти должен быть больше нуля: " + id);
        }
        this.id = id; 
    }
    
    public String getName() { 
        return this.name; 
    }
    
    public void setName(String name) { 
        if (name == null || name.trim().isEmpty()) {
            throw new InvalidPartException("Название запчасти не может быть пустым");
        }
        this.name = name; 
    }
    
    public int getQuantity() { 
        return this.quantity; 
    }
    
    public void setQuantity(int quantity) { 
        if (quantity < 0) {
            throw new InvalidPartException("Количество не может быть отрицательным: " + quantity);
        }
        this.quantity = quantity; 
    }
    
    public boolean isAvailable() { 
        return this.quantity > 0; 
    }
    
    public boolean isValid() { 
        return this.id > 0 && this.price > 0; 
    }
    
    public abstract boolean isCompatibleWith(String vehicle);
    public abstract PartType getType();
    
    // Методы для клонирования
    @Override
    public AutoPart clone() {
        try {
            return (AutoPart) super.clone();
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }
    
    public abstract AutoPart deepClone();
    
    // Реализация Comparable для шаблонных функций
    @Override
    public int compareTo(AutoPart other) {
        return Double.compare(this.price, other.price);
    }
}