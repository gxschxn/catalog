import java.util.ArrayList;
import java.util.List;

public class EnginePart extends AutoPart {
    private String engineType;
    private List<String> compatibleVehicles;

    public EnginePart(int id, String name, double price, String engineType) {
        super(id, name, price);
        
        // Использование this для устранения неоднозначности
        this.engineType = engineType;
        this.compatibleVehicles = new ArrayList<>();
        
        try {
            this.initializeCompatibleVehicles();
        } catch (Exception e) {
            System.err.println("Ошибка инициализации совместимых автомобилей: " + e.getMessage());
            this.compatibleVehicles = new ArrayList<>(); // Гарантируем, что список не null
        }
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

    public boolean isCompatibleWith(String vehicle) {
        try {
            if (vehicle == null || vehicle.trim().isEmpty()) {
                return false;
            }
            
            String lowerVehicle = vehicle.toLowerCase();
            
            if (this.engineType.equals("V6")) {
                if (lowerVehicle.contains("toyota") || 
                    lowerVehicle.contains("honda") ||
                    lowerVehicle.contains("nissan")) return true;
            } else if (this.engineType.contains("EJ")) {
                if (lowerVehicle.contains("subaru")) return true;
            } else if (this.engineType.equals("V12")) {
                if (lowerVehicle.contains("ferrari") || 
                    lowerVehicle.contains("lamborghini")) return true;
            }
            
            for (String v : this.compatibleVehicles) {
                if (v.equals(lowerVehicle)) return true;
            }
            return false;
            
        } catch (Exception e) {
            System.err.println("Ошибка проверки совместимости: " + e.getMessage());
            return false;
        }
    }

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
    
    // Геттер для engineType с использованием this
    public String getEngineType() {
        return this.engineType;
    }
}