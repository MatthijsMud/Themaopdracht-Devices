#include "EventHandler.hpp"
#include "EventSource.hpp"

EventHandler::EventHandler(unsigned long int pollInterval) :
	rtos::task<>{"EventHandler"},
	pollClock{this, pollInterval, "EventHandler"}
{
	
}

void EventHandler::addEventSource(EventSource & source)
{
	if (eventSourceCount < MAX_N_EVENT_SOURCES)
	{
		eventSources[eventSourceCount] = &source;
	}
}

void EventHandler::main()
{
	while(true)
	{
		// If there are no listeners, there is no point in polling them. Avoid 
		// wasting clock cycles by suspending this task.
		if (eventSourceCount)
		{
			this->suspend();
		}
		else
		{
			while(true)
			{
				if (eventSourceCount)
				{
					wait(pollClock);
					for (size_t i=0; i < eventSourceCount; ++i)
					{
						eventSources[i]->poll();
					}
				}
			}
		}
	}
}
