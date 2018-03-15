#include "ReceiveIRController.hpp"


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


void ReceiveIRController::main(){
	IR_Receiver ir_receiver{};

	rtos::timer timeOut ( this, "timeOut");
	rtos::clock bitDelay ( this, 800 , "bitDelay");
	rtos::timer repeatDelay ( this, "repeatDelay");

	rtos::clock checkDelay ( this, 200 , "checkDelay");

	uint64_t currentBits = 0;
	uint64_t message1 = 0;
	uint64_t message2 = 0;
	//uint64_t repeatBits = 0;
	auto lastMessageTimestamp = hwlib::now_us();

	bool result1;
	bool result2;

	for(;;){
		wait( checkDelay );
		if( ir_receiver.getValue() ){
			//hwlib::cout << "[" __FILE__ "]: last message was " <<  hwlib::now_us() - lastMessageTimestamp << " ago\n";
			//hwlib::cout << "Received startbit";
			// check if repeattimer hasnt expired yet
			bool isRepeating = false;
			auto now = hwlib::now_us() - lastMessageTimestamp;
			if ( now < 4000'000 && now > 2500'000 ){
				//hwlib::cout << "This is just a tribute\n";
				isRepeating = true;
			}
			currentBits = 1;
			for(int i = 0; i < 47; i++){
				if (i == 2 && currentBits != 6){
					break; // if no startbit is received stop doing things
				}
				wait( bitDelay );
				currentBits = (currentBits << 1) | ir_receiver.getValue();
				
			}
			//hwlib::cout << "[" __FILE__ "]: received message so far: " << currentBits << "\n";
			if (currentBits > 211106232532992){ // startbit + any other bit high

				/*repeatDelay.set( 3000 );
				wait( repeatDelay );
				for(int i = 0; i < 48; i++){
					wait( bitDelay );
					repeatBits = (repeatBits << 1) | ir_receiver.getValue();
					
				}*/
				//hwlib::cout << currentBits << "\n" << repeatBits << "\n";
				
				if (isRepeating) {
					message2 = bitsToMessage( currentBits );
					//bool result1 = checkChecksum( message1 );
					result2 = checkChecksum( message2 );
					//hwlib::cout <<"[" __FILE__ "] ";
					//hwlib::cout << "Message : " << currentBits << "\n";
					/*for(int i = 0; i<48; i++){
						hwlib::cout << ( (message1 >> (47 - i) ) & 1 );
					}*/
					//hwlib::cout << "\nChecksum 1 = " << result1 << "\n";
					/*for(int i = 0; i<48; i++){
						hwlib::cout << ( (message2 >> (47 - i) ) & 1 );
					}*/
					//hwlib::cout << "\nChecksum 2 = " << result2 << "\n\n\n";
					if ( result2 && (!result1) ){
						notifyListeners( message2 );						
					}
				} else {
					message1 = bitsToMessage( currentBits );
					result1 = checkChecksum( message1 );
					if ( result1 ){
						notifyListeners( message1 );
					}
				}
				lastMessageTimestamp = hwlib::now_us();
				timeOut.set( 2500'000 );
				wait( timeOut );
				//bool result2 = checkChecksum( bitsToMessage(repeatBits) );
			}
		}

	}

}
