#include <ReceiveIRController.hpp>

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

void main(){
    
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
   
	// wait for the PC console to start
	hwlib::wait_ms( 500 );

	return 0;
}