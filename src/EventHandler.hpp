#ifndef DEVICES_EVENT_HANDLER_HPP
#define DEVICES_EVENT_HANDLER_HPP

#include <rtos.hpp>

// Forward declaration; implementation only needed in the body.
class EventSource;

//! @brief 
//!
//! 
class EventHandler : public rtos::task<>
{
	
private:
	static constexpr size_t MAX_N_EVENT_SOURCES = 10;
	
private:
	// Array of EventSource pointers.
	EventSource* eventSources[MAX_N_EVENT_SOURCES];

private:
	rtos::clock pollClock;

private:
	size_t eventSourceCount;
	
public:
	//! Creates a class that polls all specified event sources after the specified
	//! amount of time.
	//!
	//! @param pollInterval Minimal amount of time between polls. Please use the
	//! defined macros (US, MS, S) to define the amount of time to wait.
	EventHandler(unsigned long int pollInterval);

public:
	//! Adds an EventSource to poll by this handler.
	//!
	//! This function should be invoked before running rtos. All parts should be
	//! known upfront given it is an embeded system. As the system is supposed to
	//! keep running after starting it, there should be no need to remove the
	//! event sources; hence the lack of a "removeEventSource" method.
	//!
	//! @param eventSource EventSource to add to the sources. EventHandler does
	//! not manage its lifetime, make sure it outlives this handler.
	void addEventSource(EventSource & eventSource);

private:
	//! The body responsibe for polling 
	void main() override;
};

#endif // DEVICES_EVENT_HANDLER_HPP
