// main.ino
// ============================================
// RESPONSABILIDAD: Orquestar arranque y bucle principal del sistema.
// No sabe como hacer nada: solo llama a cada modulo en el orden correcto.
// ============================================

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logo.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"

// Estados de la maquina de arranque y marca de tiempo de su ventana
bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    Serial.println(F("[BOOT] sistema de ojos OLED"));

    // TODO 1.5: Escribe las llamadas de los pasos 1 a 4 para dejar el bus y el panel listos.
    initI2C();
    scanI2C();
    testI2CDevice();

    // TODO 2.4: Escribe las llamadas de los pasos 5 y 6 para pintar el logo y ejecutar el POST de pantalla.
    initDisplay();
    showLogo();
    testDisplay();

    // TODO 3.4: Escribe la llamada del paso 7 para dejar los ojos listos.
    initEyes();

    // TODO 4.3: Escribe la llamada del paso 8, publica la ayuda y arma la ventana de arranque.
    printHelp();
    bootTime = millis();
}

void loop() {
    // TODO 2.4 (continuación): Mientras la ventana de arranque no expire, mantén el logo
    // en pantalla; al expirar, cambia de estado y repórtalo por el monitor.
    if (!bootComplete) {
        if (millis() - bootTime > LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[FSM] BOOT -> RUN"));
        } else {
            showLogo();
        }
        return;
    }

    // TODO 4.3 (continuación): Con el arranque terminado, atiende la consola en cada
    // vuelta y deja que la animación avance un paso sin bloquear el bucle.
    updateEyes();
    debugSerialTick();
}