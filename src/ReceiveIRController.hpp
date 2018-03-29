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

		//! The current amount of registered listeners
		int listenerCount=0;

		//! An array containing references to the registered listeners
		IRListener * registeredListeners [10];

		//! Receives a valid message by waiting for getMessage to return, checks the received message via the method in the Message class isValid
		//! If the message is valid the listeners are invoked using the method notifyListeners
		void main();
		
		//! Notifies the listeners in the listener array by calling their messageReceived method
		void notifyListeners(Message theMessage);

		//! Waits for a startbit and records subsequent bits into a message; returns prematurely with an empty message if invalid bits are received
		int getMessageIndex(const uint16_t theMessage, int index);
		
	private:

		//! An IR_Receiver instance of the boundary class
		IR_Receiver receiver{};

	private:

		rtos::timer bitTime;
		
	private:

		//! Waits for the startbit and then returns
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

		//! Translates 3 timeframes of high/low to a single message bit
		Bit getBit();

	private:

		//! Records the received bits using getBit after waitStartBit was called to wait for a startbit
		Message getMessage();
		
	public:

		ReceiveIRController();

		//! Adds a listener to the array of listeners by reference
		//! A valid listener is any class that implements the interface IRListener
		void addListener(IRListener & theListener);
};


#endif
