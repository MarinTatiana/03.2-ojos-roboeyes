// debug_serial.h
// ============================================
// RESPONSABILIDAD: Leer comandos del Monitor Serie y mostrar la ayuda.
// No sabe nada de: bus I2C, OLED, logos ni animacion interna de los ojos.
// ============================================

#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include <Arduino.h>
#include "config.h"
#include "eyes.h"

// TODO 4.1: Publica el bloque de ayuda con las 7 expresiones y la tecla de ayuda.
inline void printHelp() {
    Serial.println(F("[DEBUG] === AYUDA DE COMANDOS ==="));
    Serial.println(F("[DEBUG] 1-7: Cambiar expresion de los ojos"));
    Serial.println(F("[DEBUG] h: Mostrar esta ayuda"));
}

// TODO 4.2: Atiende el puerto sin bloquear: una tecla, respuesta inmediata; teclas 1 a 7 cambian la expresión, h repite la ayuda, los caracteres de control se ignoran en silencio.
inline void debugSerialTick() {
    if (Serial.available() > 0) {
        char c = Serial.read();
        if (c < 32) {
            return; // Ignorar caracteres de control en silencio
        }
        if (c >= '1' && c <= '7') {
            setEyesMood(c);
            Serial.print(F("[DEBUG] Expresion cambiada por tecla: "));
            Serial.println(c);
        } else if (c == 'h' || c == 'H') {
            printHelp();
        } else {
            Serial.print(F("[DEBUG] Tecla desconocida: "));
            Serial.println(c);
        }
    }
}

#endif