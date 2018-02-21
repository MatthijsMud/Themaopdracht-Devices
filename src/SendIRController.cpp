#include <ReceiveIRController.hpp>

void main(){

}

void send( ){
  for(int i = 0; i < 16; i++){
    if(message[i] == 1){
      led.on();
      task::wait_us(1600);
      led.off();
      task::wait_us(800);
    }
    else if(message[i] == 0){
      led.on();
      task::wait_us(800);
      led.off();
      task::wait_us(1600);
    }
  }

}
