#include <hwlib.hpp>
#include <rtos.hpp>
#include "ReceiveIRController.hpp"


int main()
{
	// Prevent restarting of the application by disabling the watchdog.
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::cout << "hello world";
	return 0;
}
