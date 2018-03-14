#ifndef RECEIVE_IR_CONTROLLER_HPP
#define RECEIVE_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "IRListener.hpp"
#include "IR_Receiver.hpp"
#include "Message.hpp"

class ReceiveIRController : public rtos::task<> {
	private :

		uint16_t lastMessage;
		uint16_t currentMessage;

		int listenerCount=0;
		IRListener * registeredListeners [10];

		void main();
		
		void notifyListeners(const uint16_t theMessage);

		uint16_t bitsToMessage(uint64_t theBits);
		bool getMessageIndex(const uint16_t theMessage, int index);

		bool isStartbit(rtos::clock &bitDelay, IR_Receiver &ir_receiver);
	public :

		bool checkChecksum(const uint16_t theMessage);
		ReceiveIRController() : rtos::task<>{1,"Test3"} {}
		void addListener(IRListener & theListener);
};


#endif