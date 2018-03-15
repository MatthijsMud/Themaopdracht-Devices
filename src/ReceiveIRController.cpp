#include "ReceiveIRController.hpp"


bool ReceiveIRController::getMessageIndex(const uint16_t theMessage, int index){ // index starts at 0
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
	hwlib::cout << "Registering listener\n";
	registeredListeners[listenerCount++] = &theListener;
	hwlib::cout << "Registered listener\n";
}

void ReceiveIRController::notifyListeners(uint16_t theMessage){
	if (theMessage != 0){
		for (int i = 0; i < listenerCount; i++){
			registeredListeners[i] -> messageReceived(
				Message{theMessage}
			);
		}
	}
}

uint16_t ReceiveIRController::bitsToMessage(uint64_t theBits){
	uint16_t returnMessage = 0;
	for (int i = 0; i < 16; i+=3 ){
		returnMessage &= ( (theBits & 7) == 1 ? 0 : 1 );
		returnMessage = returnMessage << 1;
		theBits = theBits >> 3;
	}
	if(checkChecksum(returnMessage)){
		return returnMessage;	
	}
	return 0;
}


void ReceiveIRController::main(){
	IR_Receiver ir_receiver{};

	rtos::timer timeOut ( this, "timeOut");
	rtos::clock bitDelay ( this, 800 , "bitDelay");
	rtos::timer repeatDelay ( this, "repeatDelay");

	rtos::clock checkDelay ( this, 200 , "checkDelay");

	uint64_t currentBits = 0;
	uint64_t repeatBits = 0;

	for(;;){
		wait( checkDelay );
		if( ir_receiver.getValue() ){

			//hwlib::cout << "Received startbit";
			currentBits = 1;
			for(int i = 0; i < 47; i++){
				wait( bitDelay );
				currentBits = (currentBits << 1) | ir_receiver.getValue();
				
			}
			repeatDelay.set( 3000 );
			wait( repeatDelay );
			for(int i = 0; i < 48; i++){
				wait( bitDelay );
				repeatBits = (repeatBits << 1) | ir_receiver.getValue();
				
			}
			//hwlib::cout << currentBits << "\n" << repeatBits << "\n";
			bool result1 = checkChecksum( bitsToMessage(currentBits) );
			hwlib::cout <<"[" __FILE__ "] ";
			//hwlib::cout << "Message : " << currentBits << "\n";
			for(int i = 0; i<48; i++){
				hwlib::cout << ( (currentBits >> i) & 1 );
			}
			hwlib::cout << "\n";
			notifyListeners( result1 ? bitsToMessage(currentBits) : bitsToMessage(repeatBits));
			timeOut.set( 4000 );
			
			wait( timeOut );
			//bool result2 = checkChecksum( bitsToMessage(repeatBits) );
		}

	}

}
