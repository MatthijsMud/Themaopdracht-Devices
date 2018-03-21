#ifndef RECEIVE_IR_CONTROLLER_HPP
#define RECEIVE_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "IRListener.hpp"
#include "IR_Receiver.hpp"
#include "Message.hpp"

class ReceiveIRController : public rtos::task<> {
private: 
	// 
	static constexpr unsigned long int BIT_DURATION = 2400;
	
	private:
		uint16_t lastMessage;
		uint16_t currentMessage;

		int listenerCount=0;
		IRListener * registeredListeners [10];

		void main();
		
		void notifyListeners(Message theMessage);
		uint16_t bitsToMessage(uint64_t theBits);
		bool checkChecksum(const uint16_t theMessage);
		int getMessageIndex(const uint16_t theMessage, int index);
		bool isStartbit(rtos::clock &bitDelay, IR_Receiver &ir_receiver);
		
		
	private:
		IR_Receiver receiver{};
	private:
		rtos::timer bitTime;
		
	private:
		void waitStartBit();
	private:
		//! Indicates what bit is received via the protocol.
		enum class Bit
		{
			Low,
			High,
			//! Means of indicating something went wrong while receiving the bit.
			// TODO: Determine if more return cases are needed for better diagnostics.
			Invalid
		};
	private:
		Bit getBit();
	private:
		Message getMessage();
		
	public:

		ReceiveIRController();
		void addListener(IRListener & theListener);
};


#endif
