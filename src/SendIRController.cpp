#include "SendIRController.hpp"

void SendIRController::main(){
  for(;;){
  uint16_t message = MessageChannel.read();
  hwlib::cout << "Sending : " << message << "\n";
    for (int j = 0; j < 2; j++){
      for(int i = 0; i < 16; i++){
        if(((message >> (15-i % 16)) & 1) == 1){
          led.on();
          SendIRTimer.set(1600);
          wait(SendIRTimer);

          led.off();
          SendIRTimer.set(800);
          wait(SendIRTimer);
          hwlib::cout << "110";
        }
        else if(((message >> (15-i % 16)) & 1) == 0){
          led.on();
          SendIRTimer.set(800);
          wait(SendIRTimer);

          led.off();
          SendIRTimer.set(1600);
          wait(SendIRTimer);
          hwlib::cout << "001";
        }
      }
      hwlib::cout << "\n\n";
      SendIRTimer.set(3000);
      wait(SendIRTimer);
    } 
  }
  hwlib::cout << "Returned :(\n";
}

void SendIRController::RequestSend(uint16_t incommingMessage ){
  MessageChannel.write(incommingMessage);

}
