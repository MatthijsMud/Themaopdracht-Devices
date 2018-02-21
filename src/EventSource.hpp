#ifndef DEVICES_EVENT_SOURCE_HPP 
#define DEVICES_EVENT_SOURCE_HPP

#include "NonCopyable.hpp"

//! Base class for boundary objects that provide a listener interface, but 
//! require polling.
class EventSource : public NonCopyable
{
public:
	void poll();

protected:
	~EventSource();
};

#endif // DEVICES_EVENT_SOURCE_HPP
