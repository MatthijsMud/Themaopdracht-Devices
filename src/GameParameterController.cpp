#include "GameParameterController.hpp"

GameParameterController::GameParameterController(SendIRController& sendIR):
rtos::task<>{ "GameParameterController" },
sendIR{sendIR}
{}

void GameParameterController::main(){
char key = '0';

  //TO-DO show initial screen
  //wait for user to input "A"
  while(true){
    playermessage.setData(1);
    screen.initScreen();
    do{
      key = KeyPresses.read();
    }while(key != 'A' && key != 'B' && key !='C');
    if (key == 'A'){

      Player = getPlayerNumber();
      hwlib::cout << "playernumber parameter" << Player << "\n";
      playermessage.setPlayer(Player);
    }


    else if (key == 'B'){
      //weapon strength

      Weapon = getWeaponNumber();
      playermessage.setData(Weapon);

    }

    else if (key == 'C'){
      //gameleader settings
      gameLeader();

    }
  }
}

void GameParameterController::onKeyPress(unsigned char keypad){
  KeyPresses.write(keypad);
  hwlib::cout << keypad;
}


void GameParameterController::gameLeader(){
  //wait for first key press
  char key;
  start:
  screen.gameParameterC();
  do{
    key = KeyPresses.read();
  }
  while(!std::isdigit(key));

  GameTime = (int)(key-'0');
  screen.gameParameterCCustom(GameTime);
  //wait for second key press
  do{
    key = KeyPresses.read();
  }
  while(!std::isdigit(key) && key != '#');


  if(std::isdigit(key)){
    GameTime = GameTime*10 + (int)(key - '0');
    screen.gameParameterCCustom(GameTime);
    do{
      key = KeyPresses.read();
    }
    while(key != '#');
  }

  if(key == '#'){
    if(GameTime > 0 && GameTime <= 15){
      screen.gameParameterC1();
      do{
        // TODO send game time command
        hwlib::cout << GameTime;
        gameMastermessage.setTime(GameTime);
        SendCommand(gameMastermessage);
        hwlib::cout << GameTime;

        key = KeyPresses.read();
      }while(key == '#');
    }
    else{
      goto start;
    }
  }
  do{
    key = KeyPresses.read();
  }
  while(key != '*');
  if(key == '*'){
    screen.gameParameterC2();
    do{


      gameMastermessage.setStartMessage();
      SendCommand(gameMastermessage);

      key = KeyPresses.read();
    }
    while(key == '*');
  }
}

int GameParameterController::getPlayerNumber(){
  char key;
  int playernumber = 0;
  start:
  screen.gameParameterA();
  do{
    key = KeyPresses.read();
  }
  while(!std::isdigit(key));
  playernumber = (int)(key-'0');
  screen.gameParameterACustom(playernumber);
  do{
    key = KeyPresses.read();
  }
  while(!std::isdigit(key) && key != '*');
  if(key == '*'){
    return playernumber;
  }
  else if(std::isdigit(key)){
    playernumber = playernumber*10 + (int)(key - '0');
    screen.gameParameterACustom(playernumber);

    if(playernumber > 31){
      goto start;
    }
  }
  do{
    key = KeyPresses.read();
  }
  while(key != '*');
  return playernumber;

}

int GameParameterController::getWeaponNumber(){
  char key;
  int weaponstrength = 0;
  start:
  screen.gameParameterB();
  do{
    key = KeyPresses.read();
  }
  while(!std::isdigit(key));
  weaponstrength = (int)(key-'0');
  screen.gameParameterBCustom(weaponstrength);
  do{
    key = KeyPresses.read();
  }
  while(!std::isdigit(key) && key != '*');
  if(key == '*'){
    return weaponstrength;
  }
  else if(std::isdigit(key)){
    weaponstrength = weaponstrength*10 + (int)(key - '0');
    screen.gameParameterBCustom(weaponstrength);
    if(weaponstrength > 31){
      goto start;
    }
  }
  do{
    key = KeyPresses.read();
  }
  while(key != '*');
  return weaponstrength;
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
