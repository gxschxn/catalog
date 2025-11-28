import java.util.*;

public class Cart {
    private Map<AutoPart, Integer> items;

    public Cart() {
        items = new HashMap<>();
    }

    public void addItem(AutoPart part, int qty) {
        items.put(part, items.getOrDefault(part, 0) + qty);
    }

    public void addItem(AutoPart part) {
        addItem(part, 1);
    }

    public void removeItem(AutoPart part) {
        items.remove(part);
    }

    public double getTotal() {
        double total = 0;
        for (Map.Entry<AutoPart, Integer> item : items.entrySet()) {
            total += item.getKey().getPrice() * item.getValue();
        }
        return total;
    }

    public void clear() {
        items.clear();
    }

    public int getItemCount() {
        return items.size();
    }
}
