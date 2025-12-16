import java.util.ArrayList;
import java.util.List;

public class EnginePart extends AutoPart implements Installable, Warrantable {
    private String engineType;
    private List<String> compatibleVehicles;
    private int warrantyMonths;

    public EnginePart(int id, String name, double price, String engineType) {
        super(id, name, price); // Вызов конструктора базового класса
        
        this.engineType = engineType;
        this.compatibleVehicles = new ArrayList<>();
        this.warrantyMonths = 12;
        
        // Использование protected метода из базового класса
        if (id > 100) {
            updateIdWithPrefix("PREMIUM-");
        }
        
        try {
            this.initializeCompatibleVehicles();
        } catch (Exception e) {
            System.err.println("Ошибка инициализации совместимых автомобилей: " + e.getMessage());
            this.compatibleVehicles = new ArrayList<>();
        }
    }
    
    private EnginePart(EnginePart other) {
        super(other.id, other.name, other.price);
        this.engineType = other.engineType;
        this.compatibleVehicles = new ArrayList<>(other.compatibleVehicles);
        this.warrantyMonths = other.warrantyMonths;
        this.quantity = other.quantity;
    }
    
    private void initializeCompatibleVehicles() {
        if (this.engineType.equals("V6")) {
            this.compatibleVehicles.add("toyota camry sedan");
            this.compatibleVehicles.add("toyota rav4");
            this.compatibleVehicles.add("honda accord sedan");
        } else if (this.engineType.contains("EJ")) {
            this.compatibleVehicles.add("subaru impreza");
            this.compatibleVehicles.add("subaru forester");
            this.compatibleVehicles.add("subaru wrx");
        } else if (this.engineType.equals("V12")) {
            this.compatibleVehicles.add("ferrari 488");
            this.compatibleVehicles.add("lamborghini aventador");
        } else {
            throw new IllegalArgumentException("Неизвестный тип двигателя: " + this.engineType);
        }
    }

    // Перегрузка с вызовом метода базового класса
    @Override
    public String getFullInfo() {
        String baseInfo = super.getFullInfo();
        return baseInfo + " [Двигатель: " + this.engineType + "]";
    }
    
    // Перегрузка без вызовов метода базового класса
    @Override
    public boolean isCompatibleWith(String vehicle) {
        if (vehicle == null || vehicle.trim().isEmpty()) {
            return false;
        }
        
        String lowerVehicle = vehicle.toLowerCase();
        
        // Демонстрация прямого доступа к protected полю
        boolean isPremium = this.id > 100;
        if (isPremium) {
        }
        
        if (this.engineType.equals("V6")) {
            return lowerVehicle.contains("toyota") || 
                   lowerVehicle.contains("honda") ||
                   lowerVehicle.contains("nissan");
        } else if (this.engineType.contains("EJ")) {
            return lowerVehicle.contains("subaru");
        } else if (this.engineType.equals("V12")) {
            return lowerVehicle.contains("ferrari") || 
                   lowerVehicle.contains("lamborghini");
        }
        
        for (String v : this.compatibleVehicles) {
            if (v.equals(lowerVehicle)) return true;
        }
        return false;
    }

    @Override
    public PartType getType() {
        return PartType.ENGINE;
    }

    public void addVehicle(String vehicle) {
        try {
            if (vehicle != null && !vehicle.trim().isEmpty()) {
                this.compatibleVehicles.add(vehicle.toLowerCase());
            }
        } catch (Exception e) {
            System.err.println("Ошибка добавления автомобиля: " + e.getMessage());
        }
    }
    
    // Реализация интерфейса Installable
    @Override
    public String getInstallationInstructions() {
        return "Установка двигателя: 8 часов";
    }
    
    @Override
    public int getInstallationTime() {
        return 480;
    }
    
    // Реализация интерфейса Warrantable
    @Override
    public int getWarrantyMonths() {
        return warrantyMonths;
    }
    
    @Override
    public void setWarrantyMonths(int months) {
        this.warrantyMonths = months;
    }
    
    // Демонстрация виртуального вызова
    @Override
    public void displayPartInfo() {
        System.out.print("[ДВИГАТЕЛЬ] ");
        super.displayPartInfo();
    }
    
    public String getEngineType() {
        return this.engineType;
    }
    
    @Override
    public EnginePart deepClone() {
        return new EnginePart(this);
    }
}