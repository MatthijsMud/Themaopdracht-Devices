#ifndef SEND_IR_CONTROLLER_HPP
#define SEND_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "IRListener.hpp"

class ReceiveIRController : public rtos::task<> {
	private :
		void main();

		void sendMessage(Message);
	public :

		ReceiveIRController() {}
		void addListener();
}


#endif
