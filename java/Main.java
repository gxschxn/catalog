public class Main {
    public static void main(String[] args) {
        System.out.println("=== Демонстрация системы автозапчастей ===");
        
        AutoPartsApp app = new AutoPartsApp();
        
        System.out.println("\n1. Добавляем запчасти в каталог:");
        app.addEnginePart(1, "Двигатель V6", 350000, "V6");
        app.addEnginePart(2, "Двигатель EJ204", 150000, "EJ204");
        app.addEnginePart(3, "Двигатель V12", 2500000, "V12");
        app.addWheelPart(4, "Литые диски", 80000, 17.0, "5x114.3");
        app.addWheelPart(5, "Кованые диски", 120000, 18.0, "5x100");
        
        app.showStats();
        
        System.out.println("\n2. Поиск запчастей для Toyota Camry:");
        var compatibleParts1 = app.findForVehicle("toyota camry sedan");
        System.out.println("Найдено совместимых запчастей: " + compatibleParts1.size());

        System.out.println("\n3. Поиск запчастей для Subaru Impreza:");
        var compatibleParts2 = app.findForVehicle("subaru impreza");
        System.out.println("Найдено совместимых запчастей: " + compatibleParts2.size());

        System.out.println("\n4. Поиск запчастей для Ferrari:");
        var compatibleParts3 = app.findForVehicle("ferrari 488");
        System.out.println("Найдено совместимых запчастей: " + compatibleParts3.size());
        
        System.out.println("\n5. Добавляем товары в корзину:");
        
        app.addToCart("Двигатель V6 - 350000 руб. (1)");
        app.addToCart("Литые диски - 80000 руб. (4)", 4);
        
        app.showStats();
        
        System.out.println("\n6. Оформление заказа:");
        app.checkout();
        
        System.out.println("\n=== Демонстрация завершена ===");
    }
}
