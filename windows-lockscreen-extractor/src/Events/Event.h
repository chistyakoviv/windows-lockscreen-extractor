#pragma once

enum class EventType
{
	WindowClose = 1,
	ChooseFile,
};

class Event
{
public:
	Event(EventType type);
	~Event() = default;

	virtual EventType GetType() const;
private:
	EventType m_EventType;
};
