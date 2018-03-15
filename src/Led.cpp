#include "Led.hpp"

void Led::on(){
  led.set(1);
};
void Led::off(){
  led.set(0);
};
