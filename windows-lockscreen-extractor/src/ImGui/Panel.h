#pragma once

#include "Events/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class Panel
{
public:
	using CallbackType = std::function<void(Event event)>;

	Panel() = default;
	~Panel() = default;

	virtual void render() = 0;

	void SetCallback(const CallbackType& callback) { m_Callback = callback; }

	// TODO: Refactor the code to get rid of the static functions
	static void Init(GLFWwindow* window);
	static void Begin();
	static void Dockspace();
	static void End();
	static void Shutdown();
	static void SetStaticCallback(const CallbackType& callback);

	static void OnSave();
protected:
	CallbackType m_Callback;
};
