// i2c_manager.h
// ============================================
// RESPONSABILIDAD: Hablar con el bus I2C (pines, velocidad, escaneo y verificacion).
// No sabe nada de: OLED, logos, ojos ni comandos del Monitor Serie.
// ============================================

#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

// TODO 1.1: Levanta el bus I2C compartido con los pines y la velocidad estándar.
inline void initI2C() {
    Wire.begin(21, 22);
    Wire.setClock(400000);
    Serial.print("[I2C] bus listo SDA ");
    Serial.print(21);
    Serial.print(" SCL =");
    Serial.println(22);
}

// TODO 1.2: Barre el rango completo de direcciones e informa cada dispositivo hallado y el conteo final.
inline void scanI2C() {
    Serial.println("[I2C] escaneando direcciones 1-126");
    byte count = 0;
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("[I2C] dispositivo en 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
            count++;
        }
    }
    Serial.print("[I2C] dispositivos encontrados: ");
    Serial.println(count);
}

// TODO 1.3: Sondea la dirección del panel e informa si responde o si el arranque debe detenerse.
inline void testI2CDevice() {
    Wire.beginTransmission(0x3C);
    byte error = Wire.endTransmission();
    if (error == 0) {
        Serial.print("[POST] OLED responde en 0x");
        Serial.println(0x3C, HEX);
    } else {
        Serial.println("[POST ERROR] OLED no responde en la dirección esperada");
        while (true) {
            // Detiene el arranque a propósito si el panel no responde
            delay(1000);
        }
    }
}

#endif