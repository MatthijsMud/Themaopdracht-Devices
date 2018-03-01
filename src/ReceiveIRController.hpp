#ifndef RECEIVE_IR_CONTROLLER_HPP
#define RECEIVE_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "IRListener.hpp"
#include "Message.hpp"

class ReceiveIRController : public rtos::task<> {
	private :

		uint16_t lastMessage;
		uint16_t currentMessage;

		int listenerCount;
		IRListener * registeredListeners [10];

		void main();
		bool checkChecksum(const uint16_t theMessage);
		void notifyListeners(const uint16_t theMessage);
	public :

		ReceiveIRController() {}
		void addListener(IRListener & theListener);
};


#endif