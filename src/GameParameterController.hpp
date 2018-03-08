#ifndef GAME_PARAMETER_CONTROLLER_HPP
#define GAME_PARAMETER_CONTROLLER_HPP

#include "rtos.hpp"
#include "Message.hpp"
#include "KeypadListener.hpp"
#include "IRListener.hpp"
#include <cctype>

class GameParameterController : public rtos::task<>, public KeypadListener, public IRListener{
	private :
    void main();
    char WaitForKeypress();
    int Weapon = 0;
    int Player = 0;
		int GameTime = 0;
		void SendCommand(Message Message);
		Message playermessage{0};


	public :

		GameParameterController();
    rtos::channel< char, 1 > KeyPresses{this, "KeyPresses" };
		rtos::channel< Message, 1 > MessageReceived{this, "MessageReceived" };
    void onKeyPress(unsigned char keypad) override;
		void messageReceived(const Message & message) override;
		void WaitForMessage();
		char WaitForKeypress(unsigned char WaitFor);
    int GetPlayer();
    int GetWeapon();

};
#endif
