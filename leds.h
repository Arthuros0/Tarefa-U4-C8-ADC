#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "ssd1306.h"

#define VERDE 11
#define AZUL 12
#define VERMELHO 13
#define Y_JOY 26
#define X_JOY 27
#define SW 22
#define Y_CHANNEL 0
#define X_CHANNEL 1

extern uint slice_azul, slice_vermelho;
extern volatile bool led_pwm;

void init_led(uint8_t pin);
void pwm_setup();
void joystick_setup();
void joystick_pwm_display_control(ssd1306_t *ssd);

#endif