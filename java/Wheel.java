public class Wheel extends AutoPart implements Installable {
    private double diameter;
    private String boltPattern;

    public Wheel(int id, String name, double price, double diameter, String boltPattern) {
        super(id, name, price); // Вызов конструктора базового класса
        
        this.setDiameter(diameter);
        this.setBoltPattern(boltPattern);
        
        // Использование protected метода
        if (diameter > 18) {
            updateIdWithPrefix("SPORT-");
        }
    }
    
    // Конструктор для глубокого клонирования
    private Wheel(Wheel other) {
        super(other.id, other.name, other.price);
        this.diameter = other.diameter;
        this.boltPattern = other.boltPattern;
        this.quantity = other.quantity;
    }

    @Override
    public boolean isCompatibleWith(String vehicle) {
        try {
            if (vehicle == null) return false;
            
            // Демонстрация доступа к protected полю
            if (this.id > 50) {
            }
            
            return vehicle.toLowerCase().contains("sedan") && this.diameter >= 16.0;
        } catch (Exception e) {
            System.err.println("Ошибка проверки совместимости дисков: " + e.getMessage());
            return false;
        }
    }

    @Override
    public PartType getType() {
        return PartType.WHEEL;
    }

    public String getSpecs() {
        return (int)this.diameter + " inch, " + this.boltPattern;
    }
    
    // Перегрузка виртуального метода
    @Override
    public String getFullInfo() {
        return super.getFullInfo() + " [" + getSpecs() + "]";
    }
    
    // Реализация интерфейса Installable
    @Override
    public String getInstallationInstructions() {
        return "Установка дисков: 1 час";
    }
    
    @Override
    public int getInstallationTime() {
        return 60;
    }
    
    @Override
    public void displayPartInfo() {
        System.out.print("[КОЛЕСА] ");
        super.displayPartInfo();
    }
    
    public double getDiameter() {
        return this.diameter;
    }
    
    public void setDiameter(double diameter) {
        if (diameter <= 0) {
            throw new IllegalArgumentException("Диаметр должен быть положительным: " + diameter);
        }
        this.diameter = diameter;
    }
    
    public String getBoltPattern() {
        return this.boltPattern;
    }
    
    public void setBoltPattern(String boltPattern) {
        if (boltPattern == null || boltPattern.trim().isEmpty()) {
            throw new IllegalArgumentException("Разболтовка не может быть пустой");
        }
        this.boltPattern = boltPattern;
    }
    
    @Override
    public Wheel deepClone() {
        return new Wheel(this);
    }
}