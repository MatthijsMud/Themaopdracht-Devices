#include "GameController.hpp"

GameController::GameController():
	rtos::task<>{"GameController"},
	start{this, "startFlag"}
{
	
}

void GameController::main()
{
	while(true)
	{
		wait(start);
		hwlib::cout << "Started game\n";
	}
}

void GameController::messageReceived(const Message & message)
{
	
}

void GameController::onKeyPress(unsigned char key)
{
	if (key == 'A')
	{
		start.set();
	}
}
