#include "TransferHitsController.hpp"

void TransferHitsController::waitForStartCommand(){
	while(hwlib::cin.getc_nowait() != 's'){
		hwlib::wait_ms( 400 );
	}
}

void TransferHitsController::main(){
	for(;;){
		waitForStartCommand();
		theController.logHits();
	}
}
