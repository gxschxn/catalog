public abstract class AutoPart {
    protected int id;
    protected String name;
    protected double price;
    protected int quantity;
    
    // Статическое поле для подсчета всех созданных автозапчастей
    private static int totalPartsCreated = 0;
    
    // Статическое поле для минимальной допустимой цены
    private static final double MIN_PRICE = 0.0;
    
    // Статическое исключение для некорректных данных
    public static class InvalidPartException extends RuntimeException {
        public InvalidPartException(String message) {
            super(message);
        }
    }

    public AutoPart(int id, String name, double price) {
        // Использование this для устранения неоднозначности
        this.id = id;
        this.name = name;
        this.setPrice(price); // Используем setter для проверки
        this.quantity = 0;
        
        // Увеличиваем счетчик созданных запчастей
        totalPartsCreated++;
    }

    // Статический метод для получения общего количества созданных запчастей
    public static int getTotalPartsCreated() {
        return totalPartsCreated;
    }
    
    // Статический метод для проверки корректности цены
    public static boolean isValidPrice(double price) {
        return price > MIN_PRICE;
    }
    
    // Геттеры и сеттеры с проверкой и разумным использованием this
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
    
    public String getFullInfo() {
        return this.name + " - " + (int)this.price + " руб. (" + this.id + ")";
    }
    
    public boolean isValid() { 
        return this.id > 0 && this.price > 0; 
    }
    
    public abstract boolean isCompatibleWith(String vehicle);
    public abstract PartType getType();
}