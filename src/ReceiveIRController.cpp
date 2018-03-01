#include "ReceiveIRController.hpp"
#include "IR_Receiver.hpp"

bool getMessageIndex(const uint16_t theMessage, int index){ // index starts at 0
	return ( (theMessage >> index) & 1 ) == 1;
}

bool ReceiveIRController::checkChecksum(const uint16_t theMessage){
	return ( getMessageIndex(theMessage,1) ^ getMessageIndex(theMessage,6) ) &&
		( getMessageIndex(theMessage,2) ^ getMessageIndex(theMessage,7) ) &&
		( getMessageIndex(theMessage,3) ^ getMessageIndex(theMessage,8) ) &&
		( getMessageIndex(theMessage,4) ^ getMessageIndex(theMessage,9) ) &&
		( getMessageIndex(theMessage,5) ^ getMessageIndex(theMessage,10) );
}

void ReceiveIRController::addListener(IRListener & theListener){
	registeredListeners[listenerCount++] = &theListener;
}

void ReceiveIRController::notifyListeners(uint16_t theMessage){
	if (theMessage != 0){
		for (int i = 0; i < listenerCount; i++){
			registeredListeners[i] -> messageReceived(theMessage);
		}
	}
}

uint16_t bitsToMessage(uint64_t theBits){
	uint16_t returnMessage = 0;
	for (i = 0; i < 16; i+=3 ){
		( (theBits & 7) == 1 ? 0 : 1 ) &= returnMessage;
		returnMessage << 1;
		theBits >> 3;
	}
	if checkChecksum(returnMessage){
		return returnMessage;	
	} else {
		return 0;
	}
	
}

void ReceiveIRController::main(){
    
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
   
	// wait for the PC console to start
	hwlib::wait_ms( 500 );

	IR_Receiver ir_receiver();

	rtos::timer timeOut ( this, "timeOut");
	rtos::clock bitDelay ( this, 800'000, "bitDelay");
	rtos::timer repeatDelay ( this, "repeatDelay");

	uint64_t currentBits = 0;
	auto bitCount = 0;
	bool isRepeating;

	for(;;){
		timeOut.set();
		repeatDelay.set();
		rtos::waitable result = wait(this, timeOut + bitDelay );
		if (result == bitDelay){
			(currentBits << 1) &= ir_receiver::getValue();
			bitCount++;
		}
		if (result == repeatDelay){
			isRepeating = true;
		}
		if (result == timeOut){
			isRepeating = false;
			bitCount = 0;
			currentBits = 0;
		}
		if (bitCount == 16 && isRepeating){
			notifyListeners( bitsToMessage(currentBits) );
			isRepeating = false;
			bitCount = 0;
			currentBits = 0;
		}
	}
}