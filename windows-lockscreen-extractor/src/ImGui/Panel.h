#pragma once

#include "Events/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <functional>

class Panel
{
public:
	using CallbackType = std::function<void(Event event)>;

	Panel() = default;
	~Panel() = default;

	virtual void render() = 0;

	void SetCallback(const CallbackType& callback) { m_Callback = callback; }
protected:
	CallbackType m_Callback;
};
