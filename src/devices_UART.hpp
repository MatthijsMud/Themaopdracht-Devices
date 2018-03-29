#ifndef DEVICES_UART_HPP
#define DEVICES_UART_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "GameController.hpp"

class devices_UART : public rtos::task<>{
private:

    GameController & theController;

    void waitForStartCommand();

public: 
    devices_UART(GameController & theController) : theController{ theController }{}

    void main() override;
};

#endif