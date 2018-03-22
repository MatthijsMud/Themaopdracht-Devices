#ifndef GAME_PARAMETER_CONTROLLER_HPP
#define GAME_PARAMETER_CONTROLLER_HPP

#include "rtos.hpp"
#include "Message.hpp"
#include "KeypadListener.hpp"
#include "IRListener.hpp"
#include "SendIRController.hpp"
#include "Screen.hpp"
#include <cctype>

class GameParameterController : public rtos::task<>, public KeypadListener{
	private :
    void main();
		void gameLeader();
		int getPlayerNumber();
		int getWeaponNumber();
    int Weapon = 0;
    int Player = 0;
		int GameTime = 0;
		void SendCommand(Message Message);
		Message playermessage{};
		Message gameMastermessage{};
		SendIRController& sendIR;
		Screen screen{};

	public :

		GameParameterController(SendIRController& sendIR);
    rtos::channel< char, 1 > KeyPresses{this, "KeyPresses" };
    void onKeyPress(unsigned char keypad) override;
    int GetPlayer();
    int GetWeapon();

};
#endif
