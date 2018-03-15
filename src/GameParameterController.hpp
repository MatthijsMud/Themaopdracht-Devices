#ifndef GAME_PARAMETER_CONTROLLER_HPP
#define GAME_PARAMETER_CONTROLLER_HPP

#include "rtos.hpp"
#include "Message.hpp"
#include "KeypadListener.hpp"
#include "IRListener.hpp"
#include "SendIRController.hpp"
#include "Screen.hpp"
#include <cctype>

class GameParameterController : public rtos::task<>, public KeypadListener, public IRListener{
	private :
    void main();
    char WaitForKeypress(unsigned char WaitFor = '/');
    int Weapon = 0;
    int Player = 0;
		int GameTime = 0;
		void SendCommand(Message Message);
		Message playermessage{0};
		Message gameMastermessage{0};
		SendIRController& sendIR;
		Screen screen{};

	public :

		GameParameterController(SendIRController& sendIR);
    rtos::channel< char, 1 > KeyPresses{this, "KeyPresses" };
		rtos::channel< Message, 1 > MessageReceived{this, "MessageReceived" };
    void onKeyPress(unsigned char keypad) override;
		void messageReceived(const Message & message) override;
		void WaitForMessage();
    int GetPlayer();
    int GetWeapon();

};
#endif
