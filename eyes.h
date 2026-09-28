// eyes.h
// ============================================
// RESPONSABILIDAD: Animar los ojos del OLED y aplicar la expresion elegida.
// No sabe nada de: bus I2C, logos de arranque, POST ni Monitor Serie.
// ============================================

#ifndef EYES_H
#define EYES_H

#include <Arduino.h>
#include "display.h"
#include "config.h"

// Arduino.h del ESP32 define DEFAULT como 1 y RoboEyes lo define como 0. Se
// limpia esa macro (sin uso en el core) para evitar el aviso de redefinicion.
#undef DEFAULT

#include <FluxGarage_RoboEyes.h>

// Instancia global: el sistema tiene un solo par de ojos
RoboEyes<Adafruit_SSD1306> roboEyes(display);

// TODO 3.1: Inicializa los ojos con las dimensiones del panel y el objetivo de cuadros por segundo de config.h.
inline void initEyes() {
    roboEyes.begin(OLED_WIDTH, OLED_HEIGHT, 60);
    Serial.println(F("[EYES] ojos inicializados a 60 fps"));
}

// TODO 3.2: Avanza la animación un paso sin bloquear; nunca envuelvas este paso en borrado/presentación ni en esperas.
inline void updateEyes() {
    roboEyes.update();
}

// TODO 3.3: Aplica la expresión pedida por tecla (1 a 7) y restablece la base limpia antes de calibrar.
inline void setEyesMood(char key) {
    switch (key) {
        case '1': roboEyes.setMood(DEFAULT); break;
        case '2': roboEyes.setMood(HAPPY); break;
        case '3': roboEyes.setMood(TIRED); break;
        case '4': roboEyes.setMood(ANGRY); break;
        case '5': roboEyes.setMood(HAPPY); break;
        case '6': roboEyes.setMood(TIRED); break;
        case '7': roboEyes.setMood(DEFAULT); break;
        default: break;
    }
}

#endif