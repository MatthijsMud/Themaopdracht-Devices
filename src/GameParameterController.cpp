#include "GameParameterController.hpp"

GameParameterController::GameParameterController(SendIRController& sendIR):
rtos::task<>{ "GameParameterController" },
sendIR{sendIR}
{}

void GameParameterController::main(){
char key1 = '0';
char key2 = '0';
  screen.initScreen();
  //TO-DO show initial screen
  //wait for user to input "A"
  while(true){
    if(WaitForKeypress('A')){

      screen.gameParameterA();

      key1 = WaitForKeypress('Q');

      Player = key1 - '0';
      screen.gameParameterACustom(Player);
      key2 = WaitForKeypress('Q');
      if(std::isdigit(key2)){
          Player = (int)(key1 - '0')*10 + (int)(key2 - '0');
      }
      screen.gameParameterACustom(Player);
     //1 stands for any numeric value
      playermessage.setPlayer(Player);
      if(Player == 0){
        if(WaitForKeypress('C') || key2 == 'C'){
          key1 = WaitForKeypress('Q');
          key2 = WaitForKeypress('Q');
          GameTime = key1 - '0';
          if(std::isdigit(key2)){
              GameTime = (int)(key1 - '0')*10 + (int)(key2 - '0');
          }
          gameMastermessage.setTime(GameTime);
          while(WaitForKeypress('*') || key2 == '*'){
            SendCommand(gameMastermessage);
          }
        }
      }
      else if(Player > 0){
        if(WaitForKeypress('B') || key2 == 'B'){
          screen.gameParameterB();
          key1 = WaitForKeypress('Q');

          Weapon = (int)key1-'0';
          screen.gameParameterBCustom(Weapon);
          playermessage.setData(Weapon);
          key2 = WaitForKeypress('Q');
          if(std::isdigit(key2)){
              Weapon = (int)(key1 - '0')*10 + (int)(key2 - '0');
          }
          playermessage.setData(Weapon);
          screen.gameParameterBCustom(Weapon);
          key1 = WaitForKeypress();
        label:
          if(key1 == '*'){
            suspend();
          }
          else if (key1 == '#'){
            break;
          }
          else{
            goto label;
          }
        }
      }
    }
  }
}

void GameParameterController::onKeyPress(unsigned char keypad){
  KeyPresses.write(keypad);
  hwlib::cout << keypad;
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
    return key;
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
