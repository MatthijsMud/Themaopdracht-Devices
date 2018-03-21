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

private:
	//! Counts down once the game starts and will notify the game has ended.
	rtos::timer gameTime;
	
private:
	bool canShoot;

private:
	//! Player needs to wait some time before firing again; this timer keeps track
	//! of the time they need to wait.
	rtos::timer cooldownTime;

private:
	bool isVulnerable;
	
private:
	//! Player becomes invulnerable for some time after getting hit.
	rtos::timer invulnerabilityTime;

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
	//! Enters state where the application waits for the start command.
	//!
	//! Any events - like timers/clocks, IR messages, and keypresses - are 
	//! consumed. This to avoid instances where a next state is immediatly skipped.
	void waitForStartCommand();

private:
	//! Used to delay the game after the start command.
	//!
	//! This to let the players run away from eachother.
	void waitForCountDownEnd();
	
private:
	//! Enters the state in which the game is running.
	//!
	//! This lets it handle 
	void startGame();

private:
	//! Abstraction for what shooting means.
	//!
	//! This includes constructing the appropriate message, requesting for it to
	//! be sent, and determining how much time should be waited for firing again. 
	void shoot();
	
private:
	//! Logic for getting hit.
	//!
	void handleHit(Message message);

public:
	void messageReceived(const Message & message) override;

public:
	void onKeyPress(unsigned char key) override;
};

#endif // DEVICES_GAME_CONTROLLER_HPP
