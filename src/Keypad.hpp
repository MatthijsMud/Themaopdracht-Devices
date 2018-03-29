#ifndef DEVICES_KEYPAD_HPP
#define DEVICES_KEYPAD_HPP

#include <stdint.h>
#include <hwlib.hpp>

#include "EventSource.hpp"

// Forward declaration.
class KeypadListener;

//! Keypad which behaves interupt driven.
class Keypad : public EventSource
{
private:
	//! 
	static constexpr unsigned int MAX_N_LISTENERS = 10;
	
private:
	// The hwlib keypad doesn't manage the lifetime of the matrix.
	hwlib::matrix_of_switches switches;
private:
	hwlib::keypad<16> keypad;
	
private:
	//! 
	KeypadListener* listeners[MAX_N_LISTENERS];

private:
	unsigned int listenerCount;

public:
	//! Creates a interupt driven matrix-keypad from the input and output ports.
	//!
	//! @param output Pins representing the columns of the keypad.
	//! @param input Pins representing the rows.
	Keypad(hwlib::port_oc& output, hwlib::port_in& input);

public:
	//! Adds an KeypadListener to inform about key presses.
	//!
	//! All parts should be known upfront given it is an embeded system. As the 
	//! system is supposed to keep running after starting it, there should be no 
	//! need to remove the event sources; hence the lack of a "removeEventSource" 
	//! method.
	//!
	//! @param listener KeypadListener to add to the listeners. Keypad does
	//! not manage its lifetime, make sure it outlives this class.
	void addListener(KeypadListener & listener);

public:
	//! Polls a keypad for input, and notifies the listeners when pressed.
	void poll() override;
};

#endif // DEVICES_KEYPAD_HPP
