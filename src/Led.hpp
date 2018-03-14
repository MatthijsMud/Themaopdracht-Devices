#ifndef DEVICES_LED_HPP
#define DEVICES_LED_HPP
#include <stdint.h>
#include "hwlib.hpp"

class Led{
	public:
		Led(int p); // assigned nu p niet correct
		void on();
		void off();

	private:
		int pin = 6;
		hwlib::target::d2_36kHz led1{};
};

#endif // DEVICES_LED_HPP
