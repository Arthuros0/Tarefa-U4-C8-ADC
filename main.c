#include <stdio.h>
#include "pico/stdlib.h"
#include "leds.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C

ssd1306_t ssd;

int main()
{
  stdio_init_all();
  pwm_setup();
  joystick_setup();

  i2c_init(I2C_PORT,400*1000);
  init_i2c_pins(I2C_SDA, I2C_SCL);

  init_display(&ssd, ENDERECO,I2C_PORT);

  bool cor=true;

  while (true) {
    cor=!cor;
    ssd1306_fill(&ssd,!cor);
    ssd1306_rect(&ssd,3,3,122,58,cor,!cor); //Desenha retângulo
    joystick_pwm_display_control(&ssd);
    sleep_ms(500);
  }
}
