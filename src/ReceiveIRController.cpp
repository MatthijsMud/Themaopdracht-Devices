#include "ReceiveIRController.hpp"

ReceiveIRController::ReceiveIRController() :
	rtos::task<>{"ReceiveIRController"},
	bitTime{this, "BitTime"}
{
	
}


int ReceiveIRController::getMessageIndex(const uint16_t theMessage, int index){ // index starts at 0
	return ( (theMessage >> (15 - index) ) & 1 );
}

bool ReceiveIRController::checkChecksum(const uint16_t theMessage){
	//hwlib::cout << "Checking: " << theMessage << "\n";
	return theMessage == 0 ? false : ( getMessageIndex(theMessage,1) ^ getMessageIndex(theMessage,6) ) == getMessageIndex(theMessage,11) &&
		 ( getMessageIndex(theMessage,2) ^ getMessageIndex(theMessage,7) )  == getMessageIndex(theMessage,12) &&
			 ( getMessageIndex(theMessage,3) ^ getMessageIndex(theMessage,8) ) == getMessageIndex(theMessage,13) &&
				 ( getMessageIndex(theMessage,4) ^ getMessageIndex(theMessage,9) )  == getMessageIndex(theMessage,14) &&
					 ( getMessageIndex(theMessage,5) ^ getMessageIndex(theMessage,10) )  == getMessageIndex(theMessage,15);
}

void ReceiveIRController::addListener(IRListener & theListener){
	hwlib::cout << "Registering listener\n";
	registeredListeners[listenerCount++] = &theListener;
	hwlib::cout << "Registered listener\n";
}

void ReceiveIRController::notifyListeners(Message theMessage){
	for (int i = 0; i < listenerCount; i++){
		registeredListeners[i] -> messageReceived(
			theMessage
		);
	}

}

uint16_t ReceiveIRController::bitsToMessage(uint64_t theBits){
	uint16_t returnMessage = 1;
	//hwlib::cout << theBits << "\n";
	//hwlib::cout << "\nbitresult: ";
	for (int i = 0; i < 16; i++ ){
		//hwlib::cout << theBits << "\n";
		//hwlib::cout << ( (theBits & 6) == 1 );
		auto theBit = ( ( theBits >> ( 45 - (i*3) ) ) & 7 ) == 6 ? 1 : 0;
		returnMessage |= theBit;
		returnMessage = returnMessage << 1;
		//hwlib::cout << theBit <<"\n";
		//theBits = theBits >> 3;
	}
	//hwlib::cout << returnMessage << "\n";
	//if(checkChecksum(returnMessage)){
	return returnMessage;	
	//}
	//return 0;
}

void ReceiveIRController::waitStartBit()
{
	while (!receiver.getValue())
	{
		// Each bit is made up of 3 parts, to make sure variations can be detected.
		// Start of bit 1, data bit 1/0 and end of bit 0.
		// Sampling twice should give some leniency in timing.
		bitTime.set((BIT_DURATION / 3) / 2);
		wait(bitTime);
	}
}

ReceiveIRController::Bit ReceiveIRController::getBit()
{
	// Each bit is made up of 3 parts, to make sure variations can be detected.
	// Start of bit 1, data bit 1/0 and end of bit 0.
	uint8_t pattern = 0;
	for (uint8_t i=0; i<3; ++i)
	{
		pattern = ((pattern << 1) | receiver.getValue());
		bitTime.set(BIT_DURATION / 3);
		wait(bitTime);
	}
	// Determine if a valid pattern has been received by checking
	switch (pattern) {
		// 0b110
		case ((1 << 2) | (1 << 1) | (0 << 0)):
			return Bit::High;
		// 0b100
		case ((1 << 2) | (0 << 1) | (0 << 0)):
			return Bit::Low;
		default:
			break;
	}	
	return Bit::Invalid;
}

Message ReceiveIRController::getMessage()
{
	// Initialize the message.
	uint16_t data = 0;
	// No point in constructing a message if none has started.
	waitStartBit();
	for (unsigned int i=0; i<16; ++i)
	{
		// Make sure a valid bit has been received, and act accordingly.
		switch (getBit()) {
			case Bit::High: data = ((data << 1) | 1); break;
			case Bit::Low:  data = ((data << 1) | 0); break;
			// Compromised message. Create an invalid message.
			default: return Message{0};
		}
	}
	return Message{data};
}

void ReceiveIRController::main(){
	while(true)
	{
		Message message = getMessage();
		if (message.isValid())
		{
			notifyListeners(message);
		}
		// Sender sends the message twice in the hope that at least one arrives.
		// TODO: Make sure the second is disregarded if both have been received.
		// There however seems to be a bug that makes the code work as intended.
	}
}
