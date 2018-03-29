#ifndef SEND_IR_CONTROLLER_HPP
#define SEND_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Message.hpp"
#include "Led.hpp"

class SendIRController : public rtos::task<> {
	private :
		void main();
		rtos::timer SendIRTimer{this, "SendIRTimer"};
		Led led{};

	public :

		rtos::channel< uint16_t, 1 > MessageChannel{this, "MessageChannel" };
		void RequestSend(uint16_t incommingMessage);
		SendIRController();

};


#endif
