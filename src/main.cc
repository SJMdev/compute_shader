#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 

const int window_width  = 1920;
const int window_height = 1080;



// to get openGL debug info, you need a glfw version > 3.3 (4.5 should work)
// as well as a OPENGL_DEBUG_CONTEXT!
int main() {
	fmt::print("Hello, World!\n");

	// window stuff.
	GLFWwindow* window = nullptr;

	const float aspect_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);
	// glfw init.
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		window = glfwCreateWindow(window_width, window_height, "Compute Shader particle effects", NULL, NULL);
		if (window == nullptr) {
			fmt::print("failed to create window\n");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			fmt::print("failed to initialize GLAD\n");
			return -1;
		}

		// set the window region to the whole screen.
		glViewport(0, 0, window_width, window_height);
	}

	while (!glfwWindowShouldClose(window))
	{
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}