#include <ReceiveIRController.hpp>

void main(){

}

void send( ){
  uint16_t message = getMessage();
  for(int i = 0; i < 16; i++){
    if((message >> (15-i % 16)) & 1 == 1){
      led.on();
      task::wait_us(1600);
      led.off();
      task::wait_us(800);
    }
    else if(message >> (15-i % 16)) & 1 == 0){
      led.on();
      task::wait_us(800);
      led.off();
      task::wait_us(1600);
    }
  }

}
