public abstract class AutoPart {
    protected int id;
    protected String name;
    protected double price;
    protected int quantity;

    public AutoPart(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.quantity = 0;
    }

    public double getPrice() { return price; }
    
    public boolean isAvailable() { return quantity > 0; }
    
    public String getFullInfo() {
        return name + " - " + (int)price + " руб. (" + id + ")";
    }
    
    public boolean isValid() { return id > 0 && price > 0; }
    
    public abstract boolean isCompatibleWith(String vehicle);
    public abstract PartType getType();
}
