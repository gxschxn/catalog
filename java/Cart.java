import java.util.*;

public class Cart {
    private Map<AutoPart, Integer> items;
    
    // Статическое поле для максимального количества одного товара
    private static final int MAX_QUANTITY_PER_ITEM = 10;

    public Cart() {
        this.items = new HashMap<>();
    }

    public void addItem(AutoPart part, int qty) {
        try {
            if (part == null) {
                throw new IllegalArgumentException("Нельзя добавить пустую запчасть");
            }
            if (qty <= 0) {
                throw new IllegalArgumentException("Количество должно быть больше нуля: " + qty);
            }
            
            int currentQty = this.items.getOrDefault(part, 0);
            int newQty = currentQty + qty;
            
            if (newQty > MAX_QUANTITY_PER_ITEM) {
                throw new IllegalStateException(
                    "Слишком много товара '" + part.getName() + "'. Можно добавить не больше: " + MAX_QUANTITY_PER_ITEM
                );
            }
            
            this.items.put(part, newQty);
            System.out.println("Добавлено в корзину: " + part.getName() + " (количество: " + qty + ")");
            
        } catch (IllegalArgumentException e) {
            System.err.println("Ошибка при добавлении в корзину: " + e.getMessage());
        } catch (IllegalStateException e) {
            System.err.println("Ошибка корзины: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Произошла ошибка при добавлении в корзину: " + e.getMessage());
        }
    }

    public void addItem(AutoPart part) {
        this.addItem(part, 1);
    }

    public void removeItem(AutoPart part) {
        try {
            if (!this.items.containsKey(part)) {
                throw new IllegalArgumentException("Товар не найден в корзине: " + part.getName());
            }
            this.items.remove(part);
            System.out.println("Удалено из корзины: " + part.getName());
        } catch (IllegalArgumentException e) {
            System.err.println("Ошибка при удалении: " + e.getMessage());
        }
    }

    public double getTotal() {
        double total = 0;
        try {
            for (Map.Entry<AutoPart, Integer> item : this.items.entrySet()) {
                total += item.getKey().getPrice() * item.getValue();
            }
        } catch (NullPointerException e) {
            System.err.println("Ошибка при подсчете суммы: обнаружена пустая запчасть в корзине");
        }
        return total;
    }

    public void clear() {
        this.items.clear();
    }

    public int getItemCount() {
        return this.items.size();
    }
    
    // Статический метод для проверки допустимого количества
    public static boolean isValidQuantity(int quantity) {
        return quantity > 0 && quantity <= MAX_QUANTITY_PER_ITEM;
    }
}