#ifndef SEND_IR_CONTROLLER_HPP
#define SEND_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Message.hpp"
#include "Led.hpp"

//! task to send an uint16_t message with the specifies ir-protocol
class SendIRController : public rtos::task<> {
	private :
		void main();
		rtos::timer SendIRTimer{this, "SendIRTimer"};
		Led led{};

	public :
		//! channel with the messege this task has to send
		rtos::channel< uint16_t, 1 > MessageChannel{this, "MessageChannel" };

		//! function for the channel to get the message
		void RequestSend(uint16_t incommingMessage);

		SendIRController();

};


#endif
