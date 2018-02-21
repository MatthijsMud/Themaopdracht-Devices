#ifndef DEVICES_LED_HPP
#define DEVICES_LED_HPP
#include <stdint.h>
#include "hwlib.hpp"

class Led
{
public:
  Led(int p);
  void on();
  void off();



private:
int pin = 0;
hwlib::target::pin_out led1 = hwlib::target::pin_out(1, pin);
};

#endif // DEVICES_LED_HPP
Led::Led(int p){
  pin = p;
}
void Led::on(){
  led1.set(1);
};
void Led::off(){
  led1.set(0);
};
