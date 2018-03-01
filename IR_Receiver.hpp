#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class IR_Receiver {
	private:
		target::pin_in tsop_signal = target::pin_in( target::pins::d8 );
		auto tsop_gnd    = target::pin_out( target::pins::d9 );
		auto tsop_vdd = target::pin_out( target::pins::d10 );
	public:
		IR_Receiver(){
			tsop_gnd.set( 0 );
			tsop_vdd.set( 1 );
		}
		bool getValue();
};

#endif