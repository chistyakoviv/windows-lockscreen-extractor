#include "Event.h"

Event::Event(EventType type, void* data)
	: m_EventType(type), m_Data(data)
{}

EventType Event::GetType() const
{
	return m_EventType;
}

void* Event::GetData() const
{
	return m_Data;
}
