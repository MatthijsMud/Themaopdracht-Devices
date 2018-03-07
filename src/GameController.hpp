#ifndef DEVICES_GAME_CONTROLLER_HPP
#define DEVICES_GAME_CONTROLLER_HPP

#include <rtos.hpp>
#include "KeypadListener.hpp"
#include "IRListener.hpp"

class GameController : public rtos::task<>, public KeypadListener, public IRListener
{
private:
	rtos::flag start;

public:
	GameController();
	~GameController() = default;

private:
	void main() override;
	
public:
	void messageReceived(const Message & message) override;

public:
	void onKeyPress(unsigned char key) override;
};

#endif // DEVICES_GAME_CONTROLLER_HPP
