#ifndef DEVICES_LED_HPP
#define DEVICES_LED_HPP
#include <stdint.h>
#include "hwlib.hpp"

class Led{
	public:
		void on();
		void off();

	private:
		hwlib::target::d2_36kHz led{};
};

#endif // DEVICES_LED_HPP
