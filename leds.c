#include "leds.h"
#include <stdio.h>

uint slice_azul, slice_vermelho;

void pwm_setup(){
  gpio_set_function(AZUL,GPIO_FUNC_PWM);
  slice_azul=pwm_gpio_to_slice_num(AZUL);
  pwm_set_clkdiv(slice_azul,4.0);
  pwm_set_wrap(slice_azul,4095);
  pwm_set_gpio_level(AZUL,0);
  pwm_set_enabled(slice_azul,true);

  gpio_set_function(VERMELHO,GPIO_FUNC_PWM);
  slice_vermelho=pwm_gpio_to_slice_num(VERMELHO);
  pwm_set_clkdiv(slice_vermelho,4.0);
  pwm_set_wrap(slice_vermelho,4095);
  pwm_set_gpio_level(VERMELHO,0);
  pwm_set_enabled(slice_vermelho,true);
}

void joystick_setup(){
  adc_init();
  adc_gpio_init(Y_JOY);
  adc_gpio_init(X_JOY);
}

void joystick_pwm_control(){

  adc_select_input(Y_CHANNEL);
  uint32_t valor_adc=adc_read();
  printf("VRY: %d\n",valor_adc);
  if (valor_adc>=2140 || valor_adc<=1940){
    pwm_set_gpio_level(AZUL,abs(valor_adc - 2048) * 2);
  }else{
    pwm_set_gpio_level(AZUL,0);
  }
  
  adc_select_input(X_CHANNEL);
  valor_adc=adc_read();
  printf("VRX: %d\n", valor_adc);
  if(valor_adc>=2050 || valor_adc<=1850){
    pwm_set_gpio_level(VERMELHO,abs(valor_adc - 2048) * 2);
  }else{
    pwm_set_gpio_level(VERMELHO,0);
  }
  
}

int32_t abs(int32_t valor){
  if (valor<0)
  {
    return valor*(-1);
  }
  return valor;
}