// ==========================================================
//   Programación Orientada a Objetos Ejercicio 1.4
// ==========================================================

#include <Arduino.h>

// ----------------------------------------------------------
// Clase base Sensor (sensor genérico)
// ----------------------------------------------------------
class Sensor {
  protected:
    float valor;        // Última medición almacenada
    String magnitud;    // Unidad o magnitud (°C, lux, cm)

  public:
    // Constructor
    Sensor(String mag) {
      magnitud = mag;
      valor = 0.0;
    }

    // Genera una medición (simulada) - virtual para sobrescribir
    virtual void generarMedicion() {
      valor = random(0, 101); // Valor genérico
    }

    // Devuelve el valor almacenado
    float leerMedicion() {
      return valor;
    }

    // Muestra el valor por monitor serie
    void mostrar() {
      Serial.print(valor);
      Serial.print(" ");
      Serial.println(magnitud);
    }
};


// ----------------------------------------------------------
// Sensor Real LM35 (NO simulado) 

class SensorTemperaturaReal : public Sensor {
  private:
    int pin;

  public:
    SensorTemperaturaReal(int p)
      : Sensor("°C"), pin(p) {}

    void generarMedicion() override {
      int lectura = analogRead(pin);
      valor = (lectura * 5.0 / 1023.0) * 100.0;
    }
};

// Sensor REAL (LM35)
SensorTemperaturaReal sensorTempReal(A0);

void setup() {
  Serial.begin(9600);

  // Semilla para generar números aleatorios
  randomSeed(analogRead(0));

  Serial.println("=== Mediciones de Sensor de temperatura ===");
}


void loop() {

  sensorTempReal.generarMedicion();
  Serial.print("Temp LM35: ");
  sensorTempReal.mostrar();

  delay(1000); 
}
