#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class IR_Receiver {
	private:
		target::pin_in tsop_signal = target::pin_in( target::pins::d3 );
	public:
		IR_Receiver(){}
		bool getValue();
};

#endif