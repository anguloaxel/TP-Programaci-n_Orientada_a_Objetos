// ==========================================================
//   Programación Orientada a Objetos Ejercicio 1.2
// ==========================================================

class Sensor {
  protected:
    float valor;        // Último valor leído
    String magnitud;    // Unidad o magnitud (ej: grados, lux, cm)

  public:
    // Constructor
    Sensor(String mag) {
      magnitud = mag;
      valor = 0.0;
    }

    // Método que simula generar una medición
    virtual void generarMedicion() {
      // Simula un valor genérico entre 0 y 100
      valor = random(0, 101);
    }

    // Método que devuelve el valor actual
    float leerMedicion() {
      return valor;
    }

    // Método para imprimir información del sensor
    void mostrar() {
      Serial.print("Valor: ");
      Serial.print(valor);
      Serial.print(" ");
      Serial.println(magnitud);
    }
};


// ----------------------------------------------------------
// Sensor de Temperatura
// Atributo extra: temperatura mínima y máxima
// ----------------------------------------------------------
class SensorTemperatura : public Sensor {
  private:
    float tempMin;
    float tempMax;

  public:
    SensorTemperatura() : Sensor("°C"), tempMin(10), tempMax(40) {}

    // Simula una temperatura ambiente
    void generarMedicion() override {
      valor = random(tempMin * 10, tempMax * 10) / 10.0; 
    }
};

// ----------------------------------------------------------
// Sensor de Luz
// Atributo extra: nivel máximo de luz
// ----------------------------------------------------------
class SensorLuz : public Sensor {
  private:
    int maxLux;

  public:
    SensorLuz() : Sensor("lux"), maxLux(800) {}

    void generarMedicion() override {
      valor = random(0, maxLux + 1);
    }
};

// ----------------------------------------------------------
// Sensor Ultrasonido
// Atributo extra: distancia máxima
// ----------------------------------------------------------
class SensorUltrasonido : public Sensor {
  private:
    int distanciaMax;

  public:
    SensorUltrasonido() : Sensor("cm"), distanciaMax(200) {}

    void generarMedicion() override {
      valor = random(2, distanciaMax);
    }
};

