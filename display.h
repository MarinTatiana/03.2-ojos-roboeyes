// display.h
// ============================================
// RESPONSABILIDAD: Controlar el OLED SSD1306 (inicializacion y texto).
// No sabe nada de: ojos, logos, POST ni comandos del Monitor Serie.
// ============================================

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// Instancia global: el sistema tiene una sola pantalla
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

// TODO 1.4: Inicializa el panel con el modo de alimentación interna y la dirección del panel; si falla, informa y no continúes.
inline void initDisplay() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("[DISPLAY ERROR] fallo la asignacion de SSD1306"));
        while (true);
    }
    Serial.println(F("[DISPLAY] SSD1306 inicializado 128x64 a 400 kHz"));
}

// Ejemplo de uso de la API del panel: imprime una linea de texto y la presenta.
inline void showText(const __FlashStringHelper* texto, int x, int y, uint8_t tamano) {
    display.setTextSize(tamano);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(texto);
    display.display();
}

#endif