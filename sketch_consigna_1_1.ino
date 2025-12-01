// ==========================================================
//   Programación Orientada a Objetos Ejercicio 1.1
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
