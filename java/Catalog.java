import java.util.*;

public class Catalog {
    private Map<String, AutoPart> parts;

    public Catalog() {
        this.parts = new HashMap<>();
    }

    public void addPart(AutoPart part) {
        try {
            if (part == null) {
                throw new IllegalArgumentException("Запчасть не может быть null");
            }
            if (!part.isValid()) {
                throw new IllegalArgumentException("Невалидная запчасть: " + part.getFullInfo());
            }
            this.parts.put(part.getFullInfo(), part);
            System.out.println("Добавлена запчасть: " + part.getFullInfo());
        } catch (IllegalArgumentException e) {
            System.err.println("Ошибка добавления в каталог: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Неожиданная ошибка при добавлении в каталог: " + e.getMessage());
        }
    }

    public AutoPart findPart(String name) {
        try {
            if (name == null || name.trim().isEmpty()) {
                return null;
            }
            return this.parts.get(name);
        } catch (Exception e) {
            System.err.println("Ошибка поиска запчасти: " + e.getMessage());
            return null;
        }
    }

    public List<AutoPart> findCompatible(String vehicle) {
        List<AutoPart> result = new ArrayList<>();
        try {
            if (vehicle == null || vehicle.trim().isEmpty()) {
                return result;
            }
            
            for (AutoPart part : this.parts.values()) {
                if (part.isCompatibleWith(vehicle)) {
                    result.add(part);
                }
            }
        } catch (Exception e) {
            System.err.println("Ошибка поиска совместимых запчастей: " + e.getMessage());
        }
        return result;
    }

    public int getSize() {
        return this.parts.size();
    }
    
    public List<AutoPart> getAllParts() {
        return new ArrayList<>(this.parts.values());
    }
}