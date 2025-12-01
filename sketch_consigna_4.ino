// =============================================================
//  Ejercicio 4: Clase Timer
//  Clase que implementa un cronómetro usando solo millis()
//  Controles por consola:
//     'A' → iniciar
//     'D' → detener
//     'R' → resetear
// =============================================================

class Timer {
  private:
    unsigned long inicio;     // Momento en que se inició el timer
    unsigned long acumulado;  // Tiempo acumulado cuando está detenido
    bool corriendo;           // Estado del timer

  public:
    // Constructor
    Timer() {
      inicio = 0;
      acumulado = 0;
      corriendo = false;
    }

    // ---------------------------------------------------------
    // Iniciar el timer (si ya estaba corriendo no se reinicia)
    // ---------------------------------------------------------
    void iniciar() {
      if (!corriendo) { 
        inicio = millis();
        corriendo = true;
      }
    }

    // ---------------------------------------------------------
    // Detener el timer y guardar el tiempo acumulado
    // ---------------------------------------------------------
    void detener() {
      if (corriendo) {
        acumulado += millis() - inicio;
        corriendo = false;
      }
    }

    // ---------------------------------------------------------
    // Resetear totalmente el cronómetro
    // ---------------------------------------------------------
    void resetear() {
      inicio = millis();
      acumulado = 0;
      corriendo = false;
    }

    // ---------------------------------------------------------
    // Obtener el tiempo transcurrido en milisegundos
    // ---------------------------------------------------------
    unsigned long tiempo() {
      if (corriendo) {
        return acumulado + (millis() - inicio);
      } else {
        return acumulado;
      }
    }

    // ---------------------------------------------------------
    // Mostrar por consola en formato legible
    // ---------------------------------------------------------
    void imprimir() {
      unsigned long t = tiempo();
      Serial.print("Tiempo: ");
      Serial.print(t);
      Serial.println(" ms");
    }
};


// =============================================================
//  PROGRAMA PRINCIPAL
// =============================================================
Timer cronometro;   // Instancia del cronómetro


void setup() {
  Serial.begin(9600);
  Serial.println("=== Cronometro listo ===");
  Serial.println("A = iniciar | D = detener | R = resetear");
}


void loop() {

  // ----------------------------------------------------
  //  Captura de comandos por consola serie
  // ----------------------------------------------------
  if (Serial.available()) {
    char c = Serial.read();

    if (c == 'A') {
      cronometro.iniciar();
      Serial.println("Cronometro iniciado");
    }

    else if (c == 'D') {
      cronometro.detener();
      Serial.println("Cronometro detenido");
    }

    else if (c == 'R') {
      cronometro.resetear();
      Serial.println("Cronometro reseteado");
    }
  }

  // ----------------------------------------------------
  // Mostrar el tiempo cada 1 segundo
  // ----------------------------------------------------
  static unsigned long ultimaImpresion = 0;
  if (millis() - ultimaImpresion >= 1000) {
    ultimaImpresion = millis();
    cronometro.imprimir();
  }
}
