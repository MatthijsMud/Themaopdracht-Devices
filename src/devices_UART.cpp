#include "devices_UART.hpp"

void devices_UART::waitForStartCommand(){
	while(hwlib::cin.getc_nowait() != 's'){
		hwlib::wait_ms( 400 );
	}
}

void devices_UART::main(){
	for(;;){
		waitForStartCommand();
		theController.logHits();
	}
}
