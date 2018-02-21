#include <SendIRController.hpp>

void main(){
  uint16_t message = MessageChannel.read()
  for (int j = 0; j < 2; j++){
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
    task::wait_ms(3);
  }
}

void RequestSend(uint16_t incommingMessage ){
  MessageChannel.write(incommingMessage);

}
