#include "leds.h"
#include <stdio.h>

uint slice_azul, slice_vermelho;

volatile bool led_pwm=true;

void init_led(uint8_t pin){
  gpio_init(pin);
  gpio_set_dir(pin, GPIO_OUT);
}

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

void joystick_pwm_display_control(ssd1306_t *ssd){

  adc_select_input(Y_CHANNEL);
  uint16_t valor_adc=adc_read();
  printf("VRY: %d\n",valor_adc);
  if ((valor_adc>=2140 || valor_adc<=1940) && led_pwm){
    pwm_set_gpio_level(AZUL,abs(valor_adc - 2048) * 2);
  }else{
    pwm_set_gpio_level(AZUL,0);
  }

  uint8_t pos_y=(4095-valor_adc)/64; //Corrige inversão do eixo y do joystick;
  if(pos_y > 55){
    pos_y=55;
  }else if(pos_y < 10){
    pos_y=10;
  }

  adc_select_input(X_CHANNEL);
  valor_adc=adc_read();
  printf("VRX: %d\n", valor_adc);
  if((valor_adc>=2050 || valor_adc<=1850) && led_pwm){
    pwm_set_gpio_level(VERMELHO,abs(valor_adc - 2048) * 2);
  }else{
    pwm_set_gpio_level(VERMELHO,0);
  }
  uint8_t pos_x=valor_adc/32;
  if(pos_x > 118){
    pos_x=118;
  }else if (pos_x < 10){
    pos_x=10;
  }
  
  draw_point(ssd,pos_x,pos_y,true);
  ssd1306_send_data(ssd);
}
