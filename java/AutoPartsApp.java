import java.util.List;

public class AutoPartsApp {
    private Catalog catalog;
    private Cart cart;

    public AutoPartsApp() {
        catalog = new Catalog();
        cart = new Cart();
    }

    public void addEnginePart(int id, String name, double price, String type) {
        catalog.addPart(new EnginePart(id, name, price, type));
    }

    public void addWheelPart(int id, String name, double price, double diameter, String bolts) {
        catalog.addPart(new Wheel(id, name, price, diameter, bolts));
    }

    public List<AutoPart> findForVehicle(String vehicle) {
        return catalog.findCompatible(vehicle);
    }

    public void addToCart(String partName, int qty) {
        AutoPart part = catalog.findPart(partName);
        if (part != null) {
            cart.addItem(part, qty);
        }
    }

    public void addToCart(String partName) {
        addToCart(partName, 1);
    }

    public void checkout() {
        System.out.println("Order total: " + (int)cart.getTotal() + " руб.");
        cart.clear();
    }

    public void showStats() {
        System.out.println("Catalog size: " + catalog.getSize() + 
                         ", Cart items: " + cart.getItemCount());
    }
}
