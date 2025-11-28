import java.util.ArrayList;
import java.util.List;

public class EnginePart extends AutoPart {
    private String engineType;
    private List<String> compatibleVehicles;

    public EnginePart(int id, String name, double price, String engineType) {
        super(id, name, price);
        this.engineType = engineType;
        this.compatibleVehicles = new ArrayList<>();
        
        if (engineType.equals("V6")) {
            compatibleVehicles.add("toyota camry sedan");
            compatibleVehicles.add("toyota rav4");
            compatibleVehicles.add("honda accord sedan");
        } else if (engineType.contains("EJ")) {
            compatibleVehicles.add("subaru impreza");
            compatibleVehicles.add("subaru forester");
            compatibleVehicles.add("subaru wrx");
        } else if (engineType.equals("V12")) {
            compatibleVehicles.add("ferrari 488");
            compatibleVehicles.add("lamborghini aventador");
        }
    }

    public boolean isCompatibleWith(String vehicle) {
        if (engineType.equals("V6")) {
            if (vehicle.contains("toyota") || 
                vehicle.contains("honda") ||
                vehicle.contains("nissan")) return true;
        } else if (engineType.contains("EJ")) {
            if (vehicle.contains("subaru")) return true;
        } else if (engineType.equals("V12")) {
            if (vehicle.contains("ferrari") || 
                vehicle.contains("lamborghini")) return true;
        }
        
        for (String v : compatibleVehicles) {
            if (v.equals(vehicle)) return true;
        }
        return false;
    }

    public PartType getType() {
        return PartType.ENGINE;
    }

    public void addVehicle(String vehicle) {
        compatibleVehicles.add(vehicle);
    }
}
