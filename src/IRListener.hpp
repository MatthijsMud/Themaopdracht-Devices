#ifndef IR_LISTENER_HPP
#define IR_LISTENER_HPP

#include "NonCopyable.hpp"
#include "Message.hpp"

//! @brief Listener for messages of the IR protocol.
//!
//!
class IRListener : public NonCopyable
{
public:
	//! @brief Called when data has been received over the IR protocol.
	//!
	//! @param message Message which was received.
	//! @return void
	virtual void messageReceived(const Message & message) = 0;
	
protected:
	// Disallow the release of memory through a listener pointer.
	~IRListener();
};

#endif // IR_LISTENER_HPP
