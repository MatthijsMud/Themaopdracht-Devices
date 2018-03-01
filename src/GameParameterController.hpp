#ifndef GAME_PARAMETER_CONTROLLER_HPP
#define GAME_PARAMETER_CONTROLLER_HPP

#include "rtos.hpp"
#include "Message.hpp"
#include "KeypadListener.hpp"


class GameParameterController : public rtos::task<> {
	private :
    void main();
    char WaitForKeypress();
    int Weapon = 0;
    int Player = 0;
  

	public :

		GameParameterController() {};
    rtos::channel< char, 1 > KeyPresses{this, "KeyPresses" };
    void OnKeyPress(unsigned char keypad) override;
    int GetPlayer();
    int GetWeapon();

};
#endif
