#include "GameController.hpp"
#include "GameParameterController.hpp"
#include "SendIRController.hpp"

GameController::GameController(GameParameterController & parameters, SendIRController & sender, Screen & screen):
	rtos::task<>{ "GameController" },
	parameters{parameters},
	sender{sender},
	screen{screen},
	countdownTime{ this, "countdownTime" },
	// Make it so the game can be started out of the box. No particular reason.
	gameTimeSetting{ 5 },
	gameTime{ this, "gameTime" },
	cooldownTime{ this, "cooldownTime" },
	invulnerabilityTime{ this, "invulerabilityTime" },
	hits{},
	numberOfHits{ 0 },
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
			// Start command received.
			if(message.isStartMessage())
			{
				// The game master doesn't participate.
				if (parameters.GetPlayer() != GAME_MASTER)
				{
					break;
				}
				else
				{
					hwlib::cout << "[" __FILE__ "]: Game master doesn't participate.\n";
				}
			}
			//  While waiting, the game master can configure the time.
			// The game master is identified with playernumber 0.
			else if (message.getPlayer() == GAME_MASTER)
			{
				hwlib::cout << "[" __FILE__ "]: Setting game time " << message.getTime() << " minutes." << "\n";
				gameTimeSetting = message.getTime();
			}
			else
			{
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
	for(int i = 0; i<countDownSetting; i++){
		countdownTime.set(1'000 * 1'000);


		while(wait() != countdownTime)
		{
			continue;
		}
		screen.GCCountdown(countDownSetting - i);
	}
	hwlib::cout << "[" __FILE__ "]: Count down ended.\n";
}

void GameController::startGame()
{
	hwlib::cout << "[" __FILE__ "]: Game started.\n";
	// Key presses from before the game have started are irrelevant.
	keyPresses.clear();
	messages.clear();

	numberOfHits = 0;

	hwlib::cout << "[" __FILE__ "]: Playing " << gameTimeSetting << " minutes\n";
	// gameDurationSetting is given in minutes, but a timer expects uS.
	gameTime.set(60 * 1'000 * 1'000);

	screen.GCMain1(getRemainingHealth());
	screen.GCMain2(gameTimeSetting);

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
			screen.GCMain1(getRemainingHealth());
			screen.GCMain2(gameTimeSetting);

		} else if (event == gameTime) {
			gameTimeSetting--;
			screen.GCMain2(gameTimeSetting);
			if(gameTimeSetting == 0){
				running = false;
			}
			gameTime.set(60 * 1'000 * 1'000);

		} else {
			// Discard the event, as we were not waiting for it.
			hwlib::cout << "[" __FILE__ "]: -\n";
		}
	}
	hwlib::cout << "[" __FILE__ "]: Game ended.\n";
	logHits();
}

void GameController::shoot()
{
	if (canShoot)
	{
		hwlib::cout << "[" __FILE__ "]: Firing laser.\n";
		// Inform receipient that this player shot.
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
	uint16_t playerID = message.getPlayer();

	// Game master might send custom commands in future versions.
	// The player should not ignore those, regadrless of invulnerability.
	if (playerID == GAME_MASTER)
	{
		hwlib::cout << "[" __FILE__ "]: Ignore game master.\n";
	}
	else if (isVulnerable)
	{
		// Player's shouldn't be able to hit themselves, make sure it cannot happen
		// accidentially.
		if (playerID == parameters.GetPlayer())
		{
			hwlib::cout << "[" __FILE__ "]: Ignore self.\n";
		}
		else
		{
			hwlib::cout << "[" __FILE__ "]: Got hit " << message << ".\n";

			if (numberOfHits < MAX_NUMBER_OF_HITS)
			{
				hits[numberOfHits++] = message;
			}
			screen.GCHit(getRemainingHealth(), playerID);
			isVulnerable = false;
			// TODO: Replace with variable time for invulerability.
			invulnerabilityTime.set(1);
		}
	}
}

void GameController::logHits()
{
	hwlib::cout << "Player " << parameters.GetPlayer() << " got hit by:\n";
	for (unsigned int i=0; i<numberOfHits;++i)
	{
		Message hit = hits[i];
		hwlib::cout << "- "
			<< "player " << hit.getPlayer() << "; "
			<< "damage" << hit.getData() << "\n";
	}
	hwlib::cout << "\n";
}

int GameController::getRemainingHealth()
{
	uint16_t health = DEFAULT_HEALTH;
	for(unsigned int i=0; i<numberOfHits; ++i)
	{
		// Data is the weapon's power. Might need to get mapped to different value.
		health -= hits[i].getData();
	}
	return health;
}

void GameController::messageReceived(const Message & message)
{
	messages.write(message);
}

void GameController::onKeyPress(unsigned char key)
{
	keyPresses.write(key);
}
