#pragma once

//-=-=-=-=- GLFW -=-=-=-=-
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//-=-=-=-=- CORE -=-=-=-=-
#include "Log.h"

namespace Vulkan
{
	class Window
	{
	public:
		Window(int w, int h, std::string name);
		Window();
		~Window();

		//Deleting copy constructors
		Window(const Window&) = delete;
		Window &operator=(const Window&) = delete;

		bool should_close() { return glfwWindowShouldClose(gl_window_); }
		VkExtent2D get_extent() { return { static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT) }; }
		GLFWwindow* get_glfw_window() { return gl_window_; }
		
		void create_window_surface(VkInstance instance, VkSurfaceKHR* surface);
		
		bool was_window_resized() { return frame_buffer_resized; }
		void reset_window_resize_flag() { frame_buffer_resized = false; }

		void recentre_mouse();
	
	private:
		void init_window();
		static void framebuffer_resize_callback(GLFWwindow *gl_window, int width, int height);
		static void key_callback(GLFWwindow *gl_window, int key, int scancode, int action, int mods);
		static void mouse_callback(GLFWwindow* gl_window, double xpos, double ypos);

	public:
		int key;
		int scancode;
		int action;
		int mods;
		float xpos, ypos;
	
	private:
		int WIDTH = 800;
		int HEIGHT = 600;
		bool frame_buffer_resized = false;
		bool fullscreen;
		int* windowedX;
		int* windowedY;
		int WindowedWidth, WindowedHeight;
		
		std::string window_name_ = "Vulkan";
		GLFWwindow* gl_window_{};
		GLFWmonitor* gl_monitor;
		const GLFWvidmode* gl_vidmode;
	};
}
