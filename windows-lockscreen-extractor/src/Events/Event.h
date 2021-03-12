#pragma once

enum class EventType
{
	WindowClose = 1,
	ChooseFile,
	SaveFile,
};

class Event
{
public:
	Event(EventType type, void* data = nullptr);
	~Event() = default;

	virtual EventType GetType() const;
	virtual void* GetData() const;
private:
	EventType m_EventType;
	void* m_Data;
};
