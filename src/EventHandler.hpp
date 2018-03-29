#ifndef DEVICES_EVENT_HANDLER_HPP
#define DEVICES_EVENT_HANDLER_HPP

//! @file
//! @author Matthijs

#include <rtos.hpp>

// Forward declaration; implementation only needed in the body.
class EventSource;

//! Utility for polling boundary objects so they can pretend to be interrupt
//! driven.
class EventHandler : public rtos::task<>
{
	
private:
	//! Used to poll all listeners at a constant-ish interval.
	rtos::clock pollClock;
	
private:
	static constexpr unsigned int MAX_N_EVENT_SOURCES = 10;
	
private:
	//! Event sources which should be polled by this event handler.
	//! 
	//! Due to the environment in which this application runs, usage of the heap
	//! is undesirable. As such an array of a fixed size has been declared.
	EventSource* eventSources[MAX_N_EVENT_SOURCES];

private:
	//! Number of even sources that have been added as listeners.
	//! 
	//! @see EventHandler::eventSources
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
