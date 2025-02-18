#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

#define VERDE 11
#define AZUL 12
#define VERMELHO 13
#define Y_JOY 26
#define X_JOY 27
#define SW 22
#define Y_CHANNEL 0
#define X_CHANNEL 1

void pwm_setup();
void joystick_setup();
void joystick_pwm_control();
int32_t abs(int32_t valor);



#endif