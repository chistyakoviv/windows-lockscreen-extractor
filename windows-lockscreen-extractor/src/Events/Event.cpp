#include "Event.h"

Event::Event(EventType type)
	: m_EventType(type)
{}

EventType Event::GetType() const
{
	return m_EventType;
}
