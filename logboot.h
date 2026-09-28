// logboot.h
// ============================================
// RESPONSABILIDAD: Dibujar el logo de arranque y hacer el POST de pantalla.
// No sabe nada de: ojos, bus I2C ni comandos del Monitor Serie.
// ============================================

#ifndef LOGBOOT_H
#define LOGBOOT_H

#include <Arduino.h>
#include "display.h"
#include "logo.h"

// TODO 2.2: Pinta el marco del logo desde logo_bitmap y preséntalo en el panel.
inline void showLogo() {
    display.clearDisplay();
    display.drawBitmap(0, 0, logo_bitmap, OLED_WIDTH, OLED_HEIGHT, SSD1306_WHITE);
    display.display();
}

// TODO 2.3: Dibuja el cuadrado de autoprueba centrado e informa sus coordenadas.
inline void testDisplay() {
    int x = (OLED_WIDTH - 8) / 2;
    int y = (OLED_HEIGHT - 8) / 2;
    display.clearDisplay();
    display.fillRect(x, y, 8, 8, SSD1306_WHITE);
    display.display();
    Serial.print(F("[POST] cuadrado de pantalla en x="));
    Serial.print(x);
    Serial.print(F(" y="));
    Serial.println(y);
}

#endif