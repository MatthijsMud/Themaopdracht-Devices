#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class IR_Receiver {
	private:

		//! The pin to use for the IR led, which is set to pin d3
		target::pin_in tsop_signal = target::pin_in( target::pins::d3 );

	public:

		IR_Receiver(){}

		//! Return the value of the pin and by extention the IR led
		bool getValue();
};

#endif