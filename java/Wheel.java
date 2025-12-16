public class Wheel extends AutoPart {
    private double diameter;
    private String boltPattern;

    public Wheel(int id, String name, double price, double diameter, String boltPattern) {
        super(id, name, price);
        
        // Использование this и валидация
        this.setDiameter(diameter);
        this.setBoltPattern(boltPattern);
    }

    public boolean isCompatibleWith(String vehicle) {
        try {
            if (vehicle == null) return false;
            return vehicle.toLowerCase().contains("sedan") && this.diameter >= 16.0;
        } catch (Exception e) {
            System.err.println("Ошибка проверки совместимости дисков: " + e.getMessage());
            return false;
        }
    }

    public PartType getType() {
        return PartType.WHEEL;
    }

    public String getSpecs() {
        return (int)this.diameter + " inch, " + this.boltPattern;
    }
    
    // Геттеры и сеттеры с валидацией
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
}