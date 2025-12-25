#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <vector>

enum class EventType
{
	Resize = 0,
	MouseClick,
	MouseMove,
	KeyPressed,
	Scroll
};

class Event
{
  public:
	virtual ~Event() {};

	typedef const char* DescriptorType;

	virtual DescriptorType Type() const = 0; // Replaced const char* with DescriptorType
};

class ResizeEvent : public Event
{
  public:
	ResizeEvent() {};
	virtual ~ResizeEvent() {};

	unsigned int width, height;

	static constexpr DescriptorType descriptor = "ResizeEvent"; // Replaced const char* with DescriptorType

	virtual DescriptorType Type() const // Replaced const char* with DescriptorType
	{
		return descriptor;
	}
};

class MouseClickEvent : public Event
{
  public:
	MouseClickEvent() {};
	virtual ~MouseClickEvent() {};

	int key, action;

	static constexpr DescriptorType descriptor = "MouseClickEvent"; // Replaced const char* with DescriptorType

	virtual DescriptorType Type() const // Replaced const char* with DescriptorType
	{
		return descriptor;
	}
};

class MouseMoveEvent : public Event
{
  public:
	MouseMoveEvent() {};
	virtual ~MouseMoveEvent() {};

	double x, y;

	static constexpr DescriptorType descriptor = "MouseMoveEvent"; // Replaced const char* with DescriptorType

	virtual DescriptorType Type() const // Replaced const char* with DescriptorType
	{
		return descriptor;
	}
};

class KeyEvent : public Event
{
  public:
	KeyEvent() {};
	virtual ~KeyEvent() {};

	int keycode;
	int action;

	static constexpr DescriptorType descriptor = "KeyEvent"; // Replaced const char* with DescriptorType

	virtual DescriptorType Type() const // Replaced const char* with DescriptorType
	{
		return descriptor;
	}
};

class ScrollEvent : public Event
{
  public:
	ScrollEvent() {};
	virtual ~ScrollEvent() {};

	double scrollX, scrollY;

	static constexpr DescriptorType descriptor = "ScrollEvent"; // Replaced const char* with DescriptorType

	virtual DescriptorType Type() const // Replaced const char* with DescriptorType
	{
		return descriptor;
	}
};

class Dispatcher
{
  public:
	typedef std::function<void(const Event&)> SlotType;
	Dispatcher(SlotType&& slot);

	void Post(const Event& event) const;

  private:
	SlotType observer;
};
