#include "GameController.hpp"
#include "GameParameterController.hpp"

GameController::GameController(GameParameterController & parameters):
	rtos::task<>{ "GameController" },
	parameters{parameters},
	countDownTime{ this, "countDownTime" },
	gameTime{ this, "gameEnd" },
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
	// TODO: Make the time the game goes on for variable.
	gameTime.set(5 * 1'000 * 1'000);
	
	bool running = true;
	while(running)
	{
		// Keep a reference to the event that fired to compare to other waitables.
		const auto & event = wait();
		if (event == keyPresses)
		{
			unsigned char key = keyPresses.read();
			hwlib::cout << "[" __FILE__ "]: Keypress \"" << key << "\"\n";
		} else if (event == gameTime) {
			running = false;
		} else {
			// Discard the event, as we were not waiting for it.
			hwlib::cout << "[" __FILE__ "]: -\n";
		}
	}
	hwlib::cout << "[" __FILE__ "]: Game ended.\n";
}

void GameController::messageReceived(const Message & message)
{
	messages.write(message);
}

void GameController::onKeyPress(unsigned char key)
{
	keyPresses.write(key);
}
