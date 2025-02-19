#include "leds.h"
#include <stdio.h>

uint slice_azul, slice_vermelho;

volatile bool led_pwm=true;
bool led_pwm_old_red=false;
bool led_pwm_old_blue=false;

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

  adc_select_input(Y_CHANNEL);  //Seleção do canal 
  uint16_t valor_adc=adc_read();  //Leitura do valor analogico de Y
  printf("VRY: %d\n",valor_adc); //Debug do Joystick

  //Verifica se o joystick está fora da zona morta e se o pwm está ativado para ligar os led azul
  //Se não verifica se houve alteração no valor para evitar multiplas chamadas desnecessárias
  if ((valor_adc>=2140 || valor_adc<=1940) && led_pwm){
    pwm_set_gpio_level(AZUL,abs(valor_adc - 2048) * 2);
    led_pwm_old_blue=true;
  }else if(led_pwm_old_blue){
    pwm_set_gpio_level(AZUL,0);
    led_pwm_old_blue=false;
  }

  uint8_t pos_y=(4095-valor_adc)/64; //Corrige inversão do eixo y do joystick;
  //Difine limite superior e inferior do quadrador para o eixo y do display
  if(pos_y > 55){
    pos_y=55;
  }else if(pos_y < 10){
    pos_y=10;
  }

  adc_select_input(X_CHANNEL);
  valor_adc=adc_read();
  printf("VRX: %d\n", valor_adc);

  //Verifica se o joystick está fora da zona morta e se o pwm está ativado para ligar os led vermelho
  //Se não verifica se houve alteração no valor para evitar multiplas chamadas desnecessárias
  if((valor_adc>=2050 || valor_adc<=1850) && led_pwm){
    pwm_set_gpio_level(VERMELHO,abs(valor_adc - 2048) * 2);
    led_pwm_old_red=true;
  }else if(led_pwm_old_red){
    pwm_set_gpio_level(VERMELHO,0);
    led_pwm_old_red=false;
  }

  uint8_t pos_x=valor_adc/32; //Calcula pos no eixo x no display

  //Difine limite esquerdo e direito do quadrado para o eixo x do display
  if(pos_x > 118){
    pos_x=118;
  }else if (pos_x < 10){
    pos_x=10;
  }
  
  draw_point(ssd,pos_x,pos_y,true); //Desenha quadrado
  ssd1306_send_data(ssd);
}
