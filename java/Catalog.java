import java.util.*;

public class Catalog {
    private Map<String, AutoPart> parts;

    public Catalog() {
        parts = new HashMap<>();
    }

    public void addPart(AutoPart part) {
        parts.put(part.getFullInfo(), part);
    }

    public AutoPart findPart(String name) {
        return parts.get(name);
    }

    public List<AutoPart> findCompatible(String vehicle) {
        List<AutoPart> result = new ArrayList<>();
        for (AutoPart part : parts.values()) {
            if (part.isCompatibleWith(vehicle)) {
                result.add(part);
            }
        }
        return result;
    }

    public int getSize() {
        return parts.size();
    }
}
