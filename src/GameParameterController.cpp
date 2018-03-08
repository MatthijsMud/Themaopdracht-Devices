#include "GameParameterController.hpp"

GameParameterController::GameParameterController():
rtos::task<>{ "GameParameterController" }
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
      key2= WaitForKeypress('Q');
      player = key;
      if(std::isdigit(key2)){
          Player = (int)key2
      }

     //1 stands for any numeric value
      playermessage.SetPlayer(Player);
      if(Player == 0){
        if(WaitForKeypress('C')){
          GameTime = (int)WaitForKeypress('1');

          wait(KeyPresses);
          char temp = KeyPresses.read();

          if (std::isdigit(temp)){
            GameTime = GameTime*10 + (int)temp;
            if(WaitForKeypress('*')){
              SendCommand();
            }
          }
          if(temp == '*'){
            SendCommand();
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
  char last = 'x'

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

  else if{
    return key;
  }
}


void GameParameterController::SendCommand(Message Message){
  uint16_t mes  = Message.getMessage();
  SendIRController::RequestSend(mes);
}

int GameParameterController::GetWeapon(){
  return Weapon;
}
int GameParameterController::GetPlayer(){
  return Player;
}
