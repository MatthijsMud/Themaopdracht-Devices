#ifndef RECEIVE_IR_CONTROLLER_HPP
#define RECEIVE_IR_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class ReceiveIRController : public rtos::task<> {
	private :

		uint16_t lastMessage;
		uint16_t currentMessage;

		

		void main();
		bool checkChecksum(const uint16_t theMessage);
		void notifyListeners();
	public :

		ReceiveIRController() {}
		void addListener();
}


#endif