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
		//! function to set the variables for the game leader
		void gameLeader();

		//! function so the user can set the player number
		int getPlayerNumber();

		//! function so the user can set the weapon strength
		int getWeaponNumber();

		//! weapon strength variable
    int Weapon = 0;

		//! player number variable
    int Player = 0;

		//! length of the game
		int GameTime = 0;

		//! send the command of the game leader
		void SendCommand(Message Message);

		Message playermessage{};
		Message gameMastermessage{};
		SendIRController& sendIR;
		Screen screen{};
		rtos::channel< char, 1 > KeyPresses{this, "KeyPresses" };

	public :
		GameParameterController(SendIRController& sendIR);
		//! funtion for the keypress channel
    void onKeyPress(unsigned char keypad) override;

		//! function the get the player number
    int GetPlayer();

		//! function to get the weapon strength
    int GetWeapon();

};
#endif
