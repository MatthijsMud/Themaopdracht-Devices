#ifndef SEND_IR_CONTROLLER_HPP
#define SEND_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Message.hpp"

class SendIRController : public rtos::task<> {
	private :
		void main();

		void send(Message);
	public :

		SendIRController() {}

};


#endif
