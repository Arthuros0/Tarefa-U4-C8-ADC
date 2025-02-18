#include <stdio.h>
#include "pico/stdlib.h"
#include "leds.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C

#define BUTTON_A 5
#define BUTTON_SW 22 

ssd1306_t ssd;
bool led_pwm_old=false;

volatile bool cor=true;

absolute_time_t debounce_button;
void init_button(uint8_t pin);
void button_callback(uint pin, uint32_t events);

int main()
{
  stdio_init_all();
  pwm_setup();
  joystick_setup();

  init_button(BUTTON_A);
  init_button(BUTTON_SW);

  init_led(VERDE);

  i2c_init(I2C_PORT,400*1000);
  init_i2c_pins(I2C_SDA, I2C_SCL);

  init_display(&ssd, ENDERECO,I2C_PORT);

  debounce_button=delayed_by_ms(get_absolute_time(),200);

  gpio_set_irq_enabled_with_callback(BUTTON_A,GPIO_IRQ_EDGE_FALL,true,&button_callback);
  gpio_set_irq_enabled_with_callback(BUTTON_SW,GPIO_IRQ_EDGE_FALL,true,&button_callback);


  while (true) {
    ssd1306_fill(&ssd,!cor);
    ssd1306_rect(&ssd,3,3,122,58,cor,!cor); //Desenha retângulo

    joystick_pwm_display_control(&ssd);

    sleep_ms(41);
  }
}

void button_callback(uint pin, uint32_t events){
  if(time_reached(debounce_button)){
    if (pin == BUTTON_A){
      led_pwm=!led_pwm;
    }else if (pin == BUTTON_SW){
      cor=!cor;
      gpio_put(VERDE,!gpio_get(VERDE));
    }
    debounce_button=delayed_by_ms(get_absolute_time(),200);
  }
}

void init_button(uint8_t pin){
  gpio_init(pin);
  gpio_set_dir(pin,GPIO_IN);
  gpio_pull_up(pin);
}
