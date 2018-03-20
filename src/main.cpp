#include <hwlib.hpp>
#include <rtos.hpp>
#include "ReceiveIRController.hpp"

#include "EventHandler.hpp"
#include "Keypad.hpp"
#include "GameParameterController.hpp"
#include "GameController.hpp"
#include "ReceiveIRController.hpp"
#include "SendIRController.hpp"

int main()
{


	// Prevent restarting of the application by disabling the watchdog.
	WDT->WDT_MR = WDT_MR_WDDIS;

	// wait for the PC console to start

	hwlib::wait_ms( 500 );

	// Initialization of the keypad.
	namespace target = hwlib::target;
	// The pins are named after the button representation. Some characters on
	// result in invalid names, hence they are replaced with underscores.
	target::pin_oc row_123A{ target::pins::a0 };
	target::pin_oc row_456B{ target::pins::a1 };
	target::pin_oc row_789C{ target::pins::a2 };
	target::pin_oc row__0_D{ target::pins::a3 };

	target::pin_in col_147_{ target::pins::a4 };
	target::pin_in col_2580{ target::pins::a5 };
	target::pin_in col_369_{ target::pins::a6 };
	target::pin_in col_ABCD{ target::pins::a7 };

	hwlib::port_oc_from_pins rows{ row_123A, row_456B, row_789C, row__0_D };
	hwlib::port_in_from_pins cols{ col_147_, col_2580, col_369_, col_ABCD };

	Keypad keypad{rows, cols};

	ReceiveIRController receiveIRController{};
	SendIRController sendIRController{};

	//keypad.addListener();

	// Multiply by 1000 to convert from microseconds to milliseconds.
	EventHandler eventHandler{ 100 * 1'000};
	eventHandler.addEventSource(keypad);

	GameParameterController GameParameterController{sendIRController};

	GameController gameController{GameParameterController};
	keypad.addListener(gameController);
	keypad.addListener(GameParameterController);

	receiveIRController.addListener(gameController);
	//receiveIRController.addListener()
	
	class testTask : public rtos::task<>{
		SendIRController &theController;
	public:
		testTask(SendIRController &theController):rtos::task<>{"Test"}, theController{theController} {}
		void main(){
			for(;;){
				Message m{};
				m.setStartMessage();
				
				theController.RequestSend( m.getMessage() );
				hwlib::wait_ms( 6000 );
			}
		}
	};

	testTask theTask{ sendIRController };
	rtos::run();


	return 0;
}
