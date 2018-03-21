#include "GameController.hpp"
#include "GameParameterController.hpp"
#include "SendIRController.hpp"

GameController::GameController(GameParameterController & parameters, SendIRController & sender):
	rtos::task<>{ "GameController" },
	parameters{parameters},
	sender{sender},
	countDownTime{ this, "countDownTime" },
	gameTime{ this, "gameEnd" },
	cooldownTime{ this, "cooldown" },
	invulnerabilityTime{ this, "invulerability" },
	messages{ this, "messages" },
	keyPresses{ this, "keyPresses" }
{
	
}

void GameController::main()
{
	while(true)
	{
		waitForStartCommand();
		
		parameters.suspend();
		
		waitForCountDownEnd();
		startGame();
		
		parameters.resume();
	}
}

void GameController::waitForStartCommand()
{
	hwlib::cout << "[" __FILE__ "]: Waiting for start command.\n";
	while(true)
	{
		const auto & event = wait();
		if (event == messages)
		{
			Message message = messages.read();
			if(message.isStartMessage())
			{
				break;
			} else {
				hwlib::cout << "[" __FILE__ "]: Unexpected message: " << message << "\n";
			}
		}
	}
	hwlib::cout << "[" __FILE__ "]: Received start command.\n";
}

void GameController::waitForCountDownEnd()
{
	hwlib::cout << "[" __FILE__ "]: Waiting for count down.\n";
	// TODO: Make the time for countdown variable.
	countDownTime.set(3 * 1'000 * 1'000);
	while(wait() != countDownTime)
	{
		continue;
	}
	hwlib::cout << "[" __FILE__ "]: Count down ended.\n";
}

void GameController::startGame()
{
	hwlib::cout << "[" __FILE__ "]: Game started.\n";
	// Key presses from before the game have started are irrelevant.
	keyPresses.clear();
	messages.clear();
	
	// TODO: Make the time the game goes on for variable.
	gameTime.set(5 * 60 * 1'000 * 1'000);
	
	// Resetting th state so the player starts in a save way.
	canShoot = true;
	isVulnerable = true;
	
	bool running = true;
	while(running)
	{
		// Keep a reference to the event that fired to compare to other waitables.
		const auto & event = wait();
		if (event == keyPresses)
		{
			unsigned char key = keyPresses.read();
			switch (key) {
				case '*': shoot(); break;
				default: hwlib::cout << "[" __FILE__ "]: Key " << key << ".\n"; break;
			}
			
		} else if (event == messages) {
			Message message = messages.read();
			handleHit(message);
			
		} else if (event == cooldownTime) {
			canShoot = true;
			hwlib::cout << "[" __FILE__ "]: Can shoot again.\n";
			
		} else if (event == invulnerabilityTime) {
			isVulnerable = true;
			hwlib::cout << "[" __FILE__ "]: Is vulnerable again.\n";
			
		} else if (event == gameTime) {
			running = false;
			
		} else {
			// Discard the event, as we were not waiting for it.
			hwlib::cout << "[" __FILE__ "]: -\n";
		}
	}
	hwlib::cout << "[" __FILE__ "]: Game ended.\n";
}

void GameController::shoot()
{
	if (canShoot)
	{
		hwlib::cout << "[" __FILE__ "]: Firing laser.\n";
		
		Message message{};
		message.setPlayer(parameters.GetPlayer());
		message.setData(parameters.GetWeapon());
		
		sender.RequestSend(message.getMessage());
		
		canShoot = false;
		
		// TODO: Replace with variable time.
		cooldownTime.set(1);
	}
}

void GameController::handleHit(Message message)
{
	if (isVulnerable)
	{
		hwlib::cout << "[" __FILE__ "]: Got hit " << message << ".\n";
		isVulnerable = false;
		// TODO: 
		invulnerabilityTime.set(1);
	}
}

void GameController::messageReceived(const Message & message)
{
	messages.write(message);
}

void GameController::onKeyPress(unsigned char key)
{
	keyPresses.write(key);
}
