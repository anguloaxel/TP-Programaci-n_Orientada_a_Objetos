// =============================================================
// Control de LEDs según temperatura medida por sensor real
// Lee un sensor LM35 conectado al pin ANALÓGICO A0
// -------------------------------------------------------------

class SensorTemperaturaReal {

private:
    int pin;
    float temperatura;

public:
    SensorTemperaturaReal(int p) : pin(p), temperatura(0) {}

    // Leer sensor LM35
    void leerTemperatura() {
        int lectura = analogRead(pin);
        temperatura = (lectura * 5.0 / 1023.0) * 100.0;
    }

    float getTemperatura() {
        return temperatura;
    }
};


// -------------------------------------------------------------
// Tiene métodos: encender, apagar y parpadear
// -------------------------------------------------------------
class Led {

private:
    int pin;

public:
    Led(int p) : pin(p) {}

    void iniciar() {
        pinMode(pin, OUTPUT);
        apagar();
    }

    void encender() {
        digitalWrite(pin, HIGH);
    }

    void apagar() {
        digitalWrite(pin, LOW);
    }

    void parpadear(int tiempo) {
        encender();
        delay(tiempo);
        apagar();
        delay(tiempo);
    }
};


// -------------------------------------------------------------
// Instancias: sensor y tres LEDs
// -------------------------------------------------------------
SensorTemperaturaReal sensor(A0);

Led ledVerde(3);
Led ledAmarillo(4);
Led ledRojo(5);


void setup() {
    Serial.begin(9600);

    ledVerde.iniciar();
    ledAmarillo.iniciar();
    ledRojo.iniciar();
}

void loop() {

    // Leer temperatura del sensor real
    sensor.leerTemperatura();
    float T = sensor.getTemperatura();

    Serial.print("Temperatura: ");
    Serial.print(T);
    Serial.println(" °C");

    // ---------------------------------------------------------
    //               ACTIVACIÓN DE LEDS
    //
    // T < 0°C             → todos apagados
    // 0 ≤ T < 25°C        → verde fijo
    // 25 ≤ T < 50°C       → verde y amarillo fijos
    // T ≥ 50°C            → los 3 parpadean juntos
    // ---------------------------------------------------------

    if (T < 0) {
        // Todos apagados
        ledVerde.apagar();
        ledAmarillo.apagar();
        ledRojo.apagar();
    }
    else if (T < 25) {
        // Verde fijo
        ledVerde.encender();
        ledAmarillo.apagar();
        ledRojo.apagar();
    }
    else if (T < 50) {
        // Verde y amarillo fijos
        ledVerde.encender();
        ledAmarillo.encender();
        ledRojo.apagar();
    }
    else {
        // Más de 50°C → los 3 parpadean juntos
        ledVerde.parpadear(150);
        ledAmarillo.parpadear(150);
        ledRojo.parpadear(150);
    }

    delay(200);
}
