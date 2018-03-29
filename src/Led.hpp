#ifndef DEVICES_LED_HPP
#define DEVICES_LED_HPP
#include <stdint.h>
#include "hwlib.hpp"

//! class to set the d2 pin to the right configuration and set it on and off
class Led{
	public:
		//! turn the led on pin d2 on
		void on();

		//! turn the led on pin d off
		void off();

	private:
		hwlib::target::d2_36kHz led{};
};

#endif // DEVICES_LED_HPP
