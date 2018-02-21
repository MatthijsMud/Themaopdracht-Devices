#ifndef SEND_IR_CONTROLLER_HPP
#define SEND_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Message.hpp"

class SendIRController : public rtos::task<> {
	private :
		void main();


	public :

		channel< uint16_t, 1 > buffer( this, "MessageChannel" );
		void RequestSend(uint16_t incommingMessage);
		SendIRController() {}

};


#endif
