#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "ssd1306mod.h"

#define VERDE 11  
#define AZUL 12   
#define VERMELHO 13 
#define Y_JOY 26  
#define X_JOY 27  
#define Y_CHANNEL 0 //Canal do ADC vinculado ao Y_JOY
#define X_CHANNEL 1 //Canal do ADC vinculado ao X_JOY

extern uint slice_azul, slice_vermelho; //Armazena o slice do pino vermelho e azul
extern volatile bool led_pwm;           //Variável que ativa ou desativa pwm dos leds

void init_led(uint8_t pin); //Inicializa LED
void pwm_setup();           //Configura PWM
void joystick_setup();      //Configura Joystick
void joystick_pwm_display_control(ssd1306_t *ssd); //Controla LED e Display

#endif