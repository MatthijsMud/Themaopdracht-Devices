#include "GameParameterController.hpp"

GameParameterController::GameParameterController(SendIRController& sendIR):
rtos::task<>{ "GameParameterController" },
sendIR{sendIR}
{}

void GameParameterController::main(){
char key1 = '0';
char key2 = '0';
  //TO-DO show initial screen
  //wait for user to input "A"
  while(true){
    if(WaitForKeypress('A')){
      //TO-DO show on screen
      key1 = WaitForKeypress('Q');
      key2 = WaitForKeypress('Q');
      Player = (int)key1;
      if(std::isdigit(key2)){
          Player = (int)key2;
      }

     //1 stands for any numeric value
      playermessage.setPlayer(Player);
      if(Player == 0){
        if(WaitForKeypress('C') || key2 == 'C'){
          key1 = WaitForKeypress('Q');
          key2 = WaitForKeypress('Q');
          GameTime = (int)key1;
          if(std::isdigit(key2)){
              GameTime = (int)key2;
          }
          gameMastermessage.setTime(GameTime);
          while(WaitForKeypress('*') || key2 == '*'){
            SendCommand(gameMastermessage);
          }
        }
      }
      else if(Player > 0){
        if(WaitForKeypress('C')){
          Weapon = WaitForKeypress('1');
          playermessage.setData(Weapon);
        }
      }
    }
  }
}

void GameParameterController::onKeyPress(unsigned char keypad){
  KeyPresses.write(keypad);
}

void GameParameterController::messageReceived(const Message & message){
  MessageReceived.write(message);
}

void GameParameterController::WaitForMessage(){
  Message Message = MessageReceived.read();
  if(Message.isStartMessage()){
    //start the game
  }
  else{
    playermessage.setTime(Message.getTime());
  }

}

char GameParameterController::WaitForKeypress(unsigned char WaitFor){
  char key = KeyPresses.read();
  char last = 'x';

  if(key == WaitFor){
    return '1';
  }
  else if(std::isdigit(last) && WaitFor == 'Q' && std::isdigit(key)){
    return (int)last*10 + (int)key;
  }
  else if(WaitFor == 'Q' && std::isdigit(key)){
    last = key;
    return  key;
  }

  else{
    return key;
  }
}


void GameParameterController::SendCommand(Message message){
  uint16_t mes  = message.getMessage();
  sendIR.RequestSend(mes);
}

int GameParameterController::GetWeapon(){
  return Weapon;
}
int GameParameterController::GetPlayer(){
  return Player;
}
