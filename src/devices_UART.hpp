#ifndef DEVICES_UART_HPP
#define DEVICES_UART_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "GameController.hpp"

class devices_UART : public rtos::task<>{
private:
	
	//! A reference to the game controller instance
    GameController & theController;

    //! A function that returns when the istream has received a valid start command
    //! when this happens, the logHit method of GameController is called to write to the ostream
    void waitForStartCommand();

public: 

	//! The UART is initialized with a reference to the GameController for its logHit method
    devices_UART(GameController & theController) : theController{ theController }{}

    //! Endless for-loop reading the istream to find a start command using the waitForStartCommand method
    void main() override;
};

#endif