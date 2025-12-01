// ============================================================
//    EJERCICIO 3 – Clase Reporte con Lista Enlazada
//    Registra datos de un sensor real (temperatura LM35)
//    y permite consultar HISTORIAL, MIN, MAX, PROM
// ============================================================


// ------------------------------------------------------------
// Clase SensorTemperaturaReal (LM35 en A0)
// ------------------------------------------------------------
class SensorTemperaturaReal {
private:
    int pin;
    float temperatura;

public:
    SensorTemperaturaReal(int p) : pin(p), temperatura(0) {}

    void leerTemperatura() {
        int lectura = analogRead(pin);
        temperatura = (lectura * 5.0 / 1023.0) * 100.0;
    }

    float getTemperatura() { return temperatura; }
};


// ------------------------------------------------------------
//  Nodo de la Lista Enlazada
// ------------------------------------------------------------
class Nodo {
public:
    float valor;
    Nodo* siguiente;

    Nodo(float v) : valor(v), siguiente(nullptr) {}
};


// ------------------------------------------------------------
//  Clase Reporte (Lista enlazada simple)
// ------------------------------------------------------------
class Reporte {

private:
    Nodo* head;      // Puntero al primer nodo
    int cantidad;    // Cantidad de registros

public:
    Reporte() : head(nullptr), cantidad(0) {}

    // --------------------------------------------------------
    // Agregar un nuevo dato al inicio de la lista
    // --------------------------------------------------------
    void agregarDato(float v) {
        Nodo* nuevo = new Nodo(v);
        nuevo->siguiente = head;
        head = nuevo;
        cantidad++;
    }

    // --------------------------------------------------------
    // Enviar historial completo por consola
    // --------------------------------------------------------
    void mostrarHistorial() {
        Serial.println("=== HISTORIAL DE TEMPERATURAS ===");

        Nodo* actual = head;
        int index = 1;

        if (actual == nullptr) {
            Serial.println("Historial vacío.");
            return;
        }

        while (actual != nullptr) {
            Serial.print(index);
            Serial.print(") ");
            Serial.print(actual->valor);
            Serial.println(" °C");

            actual = actual->siguiente;
            index++;
        }

        Serial.println("=== FIN HISTORIAL ===\n");
    }

    // --------------------------------------------------------
    // Calcular valor mínimo
    // --------------------------------------------------------
    float minimo() {
        if (head == nullptr) return -999;

        float minVal = head->valor;
        Nodo* actual = head;

        while (actual != nullptr) {
            if (actual->valor < minVal)
                minVal = actual->valor;

            actual = actual->siguiente;
        }
        return minVal;
    }

    // --------------------------------------------------------
    // Calcular valor máximo
    // --------------------------------------------------------
    float maximo() {
        if (head == nullptr) return -999;

        float maxVal = head->valor;
        Nodo* actual = head;

        while (actual != nullptr) {
            if (actual->valor > maxVal)
                maxVal = actual->valor;

            actual = actual->siguiente;
        }
        return maxVal;
    }

    // --------------------------------------------------------
    // Calcular promedio
    // --------------------------------------------------------
    float promedio() {
        if (head == nullptr) return -999;

        float suma = 0;
        Nodo* actual = head;

        while (actual != nullptr) {
            suma += actual->valor;
            actual = actual->siguiente;
        }

        return suma / cantidad;
    }
};


// ------------------------------------------------------------
//  INSTANCIAS GLOBALES
// ------------------------------------------------------------
SensorTemperaturaReal sensor(A0);
Reporte reporte;


// ------------------------------------------------------------
//  SETUP
// ------------------------------------------------------------
void setup() {
    Serial.begin(9600);
    Serial.println("Sistema iniciado. Enviar comandos:");
    Serial.println("H → historial");
    Serial.println("MIN → mínimo");
    Serial.println("MAX → máximo");
    Serial.println("PROM → promedio");
}


// ------------------------------------------------------------
//  LOOP PRINCIPAL
// ------------------------------------------------------------
void loop() {

    // Leer temperatura real y agregar al reporte
    sensor.leerTemperatura();
    float T = sensor.getTemperatura();
    reporte.agregarDato(T);

    // Mostrar dato actual
    Serial.print("Temperatura actual: ");
    Serial.print(T);
    Serial.println(" °C");

    delay(1000);   // registro cada 1 segundo


    // --------------------------------------------------------
    // Procesar comandos desde el monitor serie
    // --------------------------------------------------------
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');

        if (cmd == "H") {
            reporte.mostrarHistorial();
        }
        else if (cmd == "MIN") {
            Serial.print("Temperatura mínima: ");
            Serial.println(reporte.minimo());
        }
        else if (cmd == "MAX") {
            Serial.print("Temperatura máxima: ");
            Serial.println(reporte.maximo());
        }
        else if (cmd == "PROM") {
            Serial.print("Temperatura promedio: ");
            Serial.println(reporte.promedio());
        }
    }
}
