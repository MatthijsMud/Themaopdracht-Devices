#ifndef DEVICES_KEYPAD_LISTENER_HPP
#define DEVICES_KEYPAD_LISTENER_HPP

#include "NonCopyable.hpp"

//! @brief 
//!
//!
class KeypadListener : public NonCopyable
{
public:
	//! @brief Listens to keypresses on the keypad.
	//! 
	//! @param key Representation of the charcter that was pressed on the keypad.
	void onKeyPress(unsigned char key);
	
protected:
	// You should not delete listeners through an interface.
	~KeypadListener();
};


#endif // DEVICES_KEYPAD_LISTENER_HPP
