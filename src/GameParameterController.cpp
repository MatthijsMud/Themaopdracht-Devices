#include "GameParameterController.hpp"

void GameParameterController::main(){
  int gameTime = 0;

  //TO-DO show initial screen
  //wait for user to input "A"
  while(true){
    if(WaitForKeypress('A')){
      //TO-DO show on screen
      Player = WaitForKeypress('1'); //1 stands for any numeric value

      if(Player == 0){
        if(WaitForKeypress('C')){
          GameTime = (int)WaitForKeypress('1');

          wait(keypresses);
          char temp = KeyPresses.read();

          if (std::isdigit(temp)){
            gametime = gametime*10 + (int)temp;
            if(WaitForKeypress('*')){
              //TO-DO send command
            }
          }
          if(temp = '*'){
            //TO-DO send command
          }
        }
      }

      if(WaitForKeypress('B')){
        //TO-DO show on screen
        Weapon = WaitForKeypress('1');
      }

    }

}

void GameParameterController::OnKeyPress(unsigned char keypad){
  KeyPresses.write(keypad);
}

int GameParameterController::WaitForKeypress(unsigned char WaitFor){
  if(!std::isdigit(WaitFor)){
    while(KeyPresses.read() != WaitFor){
      wait(keypresses);
    }
    return 1;
  }
  else{
    while(std::isdigit(KeyPresses.read())){
      wait(keypresses);
    }
    return WaitFor;
  }

}




int GameParameterController::GetWeapon(){
  return Weapon;
}
int GameParameterController::GetPlayer(){
  return Player;
}
