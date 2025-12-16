public class PartUtils {
    
    // Шаблонная функция, которая работает только с типами, реализующими Comparable
    public static <T extends Comparable<T>> T findBestMatch(T[] items, T target) {
        if (items == null || items.length == 0 || target == null) {
            return null;
        }
        
        T bestMatch = items[0];
        for (T item : items) {
            if (item.compareTo(target) >= 0 && item.compareTo(bestMatch) < 0) {
                bestMatch = item;
            }
        }
        return bestMatch;
    }
    
    // Еще одна шаблонная функция для вычисления общей стоимости
    public static <T extends AutoPart> double calculateTotalValue(List<T> parts) {
        return parts.stream()
            .mapToDouble(AutoPart::getPrice)
            .sum();
    }
    
    // Функция с ограничениями на типы (только Installable)
    public static <T extends AutoPart & Installable> int getTotalInstallationTime(List<T> parts) {
        return parts.stream()
            .mapToInt(Installable::getInstallationTime)
            .sum();
    }
}