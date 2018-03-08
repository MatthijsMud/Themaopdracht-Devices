#include "Led.hpp"

Led::Led(int p){
  pin = p;
}
void Led::on(){
  led1.set(1);
};
void Led::off(){
  led1.set(0);
};