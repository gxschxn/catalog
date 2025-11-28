public class Wheel extends AutoPart {
    private double diameter;
    private String boltPattern;

    public Wheel(int id, String name, double price, double diameter, String boltPattern) {
        super(id, name, price);
        this.diameter = diameter;
        this.boltPattern = boltPattern;
    }

    public boolean isCompatibleWith(String vehicle) {
        return vehicle.contains("sedan") && diameter >= 16.0;
    }

    public PartType getType() {
        return PartType.WHEEL;
    }

    public String getSpecs() {
        return (int)diameter + " inch, " + boltPattern;
    }
}
