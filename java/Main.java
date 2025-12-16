public class Main {
    public static void main(String[] args) {
        
        AutoPartsApp app = new AutoPartsApp();
        
        System.out.println("\n1. Добавляем запчасти в каталог:");
        
        // Корректные данные
        app.addEnginePart(1, "Двигатель V6", 350000, "V6");
        app.addEnginePart(2, "Двигатель EJ204", 150000, "EJ204");
        app.addWheelPart(4, "Литые диски", 80000, 17.0, "5x114.3");
        
        // Проверка обработки ошибок - некорректные данные
        System.out.println("\nПроверка обработки ошибок:");
        app.addEnginePart(-1, "Двигатель с ошибкой", 350000, "V6"); // Некорректный номер
        app.addWheelPart(5, "", 120000, 18.0, "5x100"); // Пустое название
        app.addEnginePart(6, "Двигатель с ошибкой цены", -1000, "V6"); // Отрицательная цена
        
        app.showStats();
        
        System.out.println("\n2. Поиск запчастей для Toyota Camry:");
        var compatibleParts1 = app.findForVehicle("toyota camry sedan");
        System.out.println("Найдено совместимых запчастей: " + compatibleParts1.size());

        // Проверка ошибок при поиске
        System.out.println("\nПроверка ошибок поиска:");
        app.findForVehicle(""); // Пустой запрос
        app.findForVehicle(null); // Null запрос
        
        System.out.println("\n3. Добавляем товары в корзину:");
        
        // Корректное добавление
        app.addToCart("Двигатель V6 - 350000 руб. (1)");
        app.addToCart("Литые диски - 80000 руб. (4)", 4);
        
        // Проверка ошибок при добавлении в корзину
        System.out.println("\nПроверка ошибок корзины:");
        app.addToCart("Несуществующая запчасть"); // Несуществующий товар
        app.addToCart("Двигатель V6 - 350000 руб. (1)", -5); // Отрицательное количество
        app.addToCart("Двигатель V6 - 350000 руб. (1)", 20); // Слишком большое количество
        
        app.showStats();
        
        System.out.println("\n4. Оформление заказа:");
        app.checkout();
        
        // Проверка ошибки при пустой корзине
        System.out.println("\nПроверка оформления пустой корзины:");
        app.checkout();
        
    }
}