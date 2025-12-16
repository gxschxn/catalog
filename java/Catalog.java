import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

// Шаблонный класс Catalog
public class Catalog<T extends AutoPart> {
    private Map<String, T> parts;
    private String catalogName;
    
    // Нешаблонные поля
    private static int totalCatalogs = 0;
    private final String catalogId;
    
    // Нешаблонные контейнеры для демонстрации
    private List<T> partsList = new ArrayList<>();  // ArrayList - аналог std::vector
    private LinkedList<T> recentlyAdded = new LinkedList<>(); // LinkedList - аналог std::list
    private Map<Integer, T> partsById = new HashMap<>(); // HashMap - аналог std::map
    
    public Catalog(String name) {
        this.parts = new HashMap<>();
        this.catalogName = name;
        this.catalogId = "CAT-" + (++totalCatalogs);
    }
    
    public Catalog() {
        this("Общий каталог");
    }
    
    // Нешаблонный метод
    public static int getTotalCatalogs() {
        return totalCatalogs;
    }
    
    // Шаблонный метод для добавления
    public void addPart(T part) {
        try {
            if (part == null) {
                throw new IllegalArgumentException("Запчасть не может быть null");
            }
            if (!part.isValid()) {
                throw new IllegalArgumentException("Невалидная запчасть: " + part.getFullInfo());
            }
            
            // Добавляем во все контейнеры
            this.parts.put(part.getFullInfo(), part);
            this.partsList.add(part);           // ArrayList
            this.recentlyAdded.addFirst(part);  // LinkedList (добавляем в начало)
            this.partsById.put(part.getId(), part); // HashMap
            
            System.out.println("Добавлена в каталог '" + catalogName + "': " + part.getFullInfo());
        } catch (IllegalArgumentException e) {
            System.err.println("Ошибка добавления в каталог: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Неожиданная ошибка при добавлении в каталог: " + e.getMessage());
        }
    }
    
    // Шаблонные методы поиска
    public T findPart(String name) {
        return parts.get(name);
    }
    
    public T findPartById(int id) {
        return partsById.get(id); // Используем HashMap для быстрого поиска
    }
    
    // Аналог std::find_if
    public Optional<T> findFirst(Predicate<T> predicate) {
        return partsList.stream()
            .filter(predicate)
            .findFirst();
    }
    
    // Аналог std::any_of
    public boolean anyMatch(Predicate<T> predicate) {
        return partsList.stream()
            .anyMatch(predicate);
    }
    
    // Аналог std::sort
    public List<T> getSortedParts(Comparator<T> comparator) {
        List<T> sorted = new ArrayList<>(partsList);
        sorted.sort(comparator);
        return sorted;
    }
    
    // Аналог std::min_element
    public Optional<T> getCheapestPart() {
        return partsList.stream()
            .min(Comparator.comparingDouble(T::getPrice));
    }
    
    // Аналог std::max_element
    public Optional<T> getMostExpensivePart() {
        return partsList.stream()
            .max(Comparator.comparingDouble(T::getPrice));
    }
    
    // Аналог std::copy_if
    public List<T> filterParts(Predicate<T> predicate) {
        return partsList.stream()
            .filter(predicate)
            .collect(Collectors.toList());
    }
    
    // Аналог std::remove_if
    public void removeParts(Predicate<T> predicate) {
        partsList.removeIf(predicate);
        // Также нужно удалить из других контейнеров
        parts.values().removeIf(predicate);
        recentlyAdded.removeIf(predicate);
        partsById.values().removeIf(predicate);
    }
    
    // Аналог std::transform
    public List<String> getAllPartNames() {
        return partsList.stream()
            .map(T::getName)
            .collect(Collectors.toList());
    }
    
    // Метод, возвращающий конкретный тип (EnginePart) - демонстрация downcasting
    @SuppressWarnings("unchecked")
    public List<EnginePart> findAllEngineParts() {
        return partsList.stream()
            .filter(part -> part instanceof EnginePart)
            .map(part -> (EnginePart) part)
            .collect(Collectors.toList());
    }
    
    // Метод, работающий с интерфейсом Installable
    public List<Installable> getAllInstallableParts() {
        return partsList.stream()
            .filter(part -> part instanceof Installable)
            .map(part -> (Installable) part)
            .collect(Collectors.toList());
    }
    
    // Нешаблонный метод
    public String getCatalogInfo() {
        return catalogId + " - " + catalogName + " (" + parts.size() + " запчастей)";
    }
    
    // Шаблонный метод с двумя параметрами типа
    public <U extends AutoPart> void mergeCatalog(Catalog<U> otherCatalog) {
        if (otherCatalog == null) return;
        
        System.out.println("Слияние каталогов: " + this.catalogName + " + " + 
                          (otherCatalog.catalogName != null ? otherCatalog.catalogName : "другой каталог"));
    }
    
    // Статистика контейнеров
    public void printContainerStats() {
        System.out.println("=== Статистика контейнеров каталога '" + catalogName + "' ===");
        System.out.println("HashMap (основной): " + parts.size());
        System.out.println("ArrayList (список): " + partsList.size());
        System.out.println("LinkedList (последние): " + recentlyAdded.size());
        System.out.println("HashMap (по ID): " + partsById.size());
    }
    
    public int getSize() {
        return this.parts.size();
    }
    
    public List<T> getAllParts() {
        return new ArrayList<>(this.partsList);
    }
    
    // Геттер для имени каталога
    public String getCatalogName() {
        return catalogName;
    }
}