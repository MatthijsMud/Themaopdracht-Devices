#ifndef DEVICES_GAME_CONTROLLER_HPP
#define DEVICES_GAME_CONTROLLER_HPP

//! @file
//! @author Matthijs

#include <rtos.hpp>
#include "KeypadListener.hpp"
#include "IRListener.hpp"
#include "Message.hpp"
#include "Screen.hpp"

// Forward declarations.
class GameParameterController;
class SendIRController;

class GameController : public rtos::task<>, public KeypadListener, public IRListener
{
private:
	//! Player id for the person who sends out the start command (among others).
	static constexpr uint16_t GAME_MASTER{0};

private:
	static constexpr uint16_t DEFAULT_HEALTH{100};

private:
	// Assuming players can hit for a minimum of 1 damage, the max number of hits
	// needs to be equal to the total health.
	static constexpr unsigned int MAX_NUMBER_OF_HITS{DEFAULT_HEALTH};

private:
	GameParameterController & parameters;

private:
	SendIRController & sender;

private:

	Screen & screen;

private:
	//! Time to wait after receiving start signal to actually start.
	//! Used to give the players time to separate.
	rtos::timer countdownTime;

private:
	//! Setting for how long each game will take.
	unsigned long int gameTimeSetting;

private:

	int countDownSetting = 5;

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
	// Serves a storage for the hits the player might receive during the game.
	Message hits[MAX_NUMBER_OF_HITS];

private:
	// Number of hits in which have been recorded. Beyond it is junk.
	unsigned int numberOfHits;

private:
	rtos::channel<Message, 2> messages;

private:
	rtos::channel<unsigned char, 4> keyPresses;

public:
	GameController(GameParameterController & paramters, SendIRController & sender, Screen & screen);
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

private:
	//! Calculates the remaining of the health based on its hits.
	//! 
	//! @see GameController::hits
	//! @see GameController::DEFAULT_HEALTH
	int getRemainingHealth();

public:
	//! Writes the hits the player received to the default output.
	void logHits();

public:
	void messageReceived(const Message & message) override;

public:
	void onKeyPress(unsigned char key) override;
};

#endif // DEVICES_GAME_CONTROLLER_HPP
