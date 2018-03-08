#ifndef DEVICES_GAME_CONTROLLER_HPP
#define DEVICES_GAME_CONTROLLER_HPP

#include <rtos.hpp>
#include "KeypadListener.hpp"
#include "IRListener.hpp"
#include "Message.hpp"

// Forward declaration.
class GameParameterController;

class GameController : public rtos::task<>, public KeypadListener, public IRListener
{
private:
	GameParameterController & parameters;
	
private:
	//! Time to wait after receiving start signal to actually start.
	//! Used to give the players time to separate.
	rtos::timer countDownTime;
	//! Counts down once the game starts and will notify the game has ended.
	rtos::timer gameTime;

private:
	rtos::channel<Message, 2> messages;

private:
	rtos::channel<unsigned char, 4> keyPresses;

public:
	GameController(GameParameterController & paramters);
	~GameController() = default;

private:
	void main() override;
	
private:
	//! 
	void waitForStartCommand();

private:
	void waitForCountDownEnd();
	
private:
	void startGame();

public:
	void messageReceived(const Message & message) override;

public:
	void onKeyPress(unsigned char key) override;
};

#endif // DEVICES_GAME_CONTROLLER_HPP
