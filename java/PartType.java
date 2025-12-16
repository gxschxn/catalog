public enum PartType {
    ENGINE(1),
    WHEEL(2),
    SUSPENSION(3),
    BODY(4);

    private final int value;

    PartType(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    public static String partTypeToString(PartType type) {
        if (type == null) {
            return "Unknown";
        }
        
        switch(type) {
            case ENGINE: return "Engine";
            case WHEEL: return "Wheel";
            case SUSPENSION: return "Suspension";
            case BODY: return "Body";
            default: return "Unknown";
        }
    }
    
    public static PartType fromValue(int value) {
        for (PartType type : PartType.values()) {
            if (type.getValue() == value) {
                return type;
            }
        }
        throw new IllegalArgumentException("Неизвестное значение типа запчасти: " + value);
    }
}