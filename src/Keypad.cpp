#include <rtos.hpp>
#include "Keypad.hpp"
#include "KeypadListener.hpp"

Keypad::Keypad(hwlib::port_oc& output, hwlib::port_in& input):
	switches{output, input},
	keypad{switches, "123A456B789C*0#D"},
	listenerCount{0}
{
	
}

void Keypad::addListener(KeypadListener & listener)
{
	if (listenerCount < MAX_N_LISTENERS)
	{
		listeners[listenerCount++] = &listener;
	}
}

void Keypad::poll()
{
	unsigned char pressedKey = '\0';
	if(keypad.char_available())
	{
		pressedKey = keypad.getc();
		hwlib::cout << pressedKey << "\n";
		
		for (unsigned int i=0; i < listenerCount; ++i)
		{
			listeners[i]->onKeyPress(pressedKey);
		}
	}
}
