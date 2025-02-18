#include <stdio.h>
#include "pico/stdlib.h"
#include "leds.h"



int main()
{
  stdio_init_all();
  pwm_setup();
  joystick_setup();

  while (true) {
    joystick_pwm_control();
    sleep_ms(500);
  }
}
