#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <glm/glm.hpp>

#include <vector>

const int window_width  = 1920;
const int window_height = 1080;

// camera (perspective)
const float fov = 90.0f;
const float aspect_ratio = static_cast<float>(window_width) / static_cast<float>(window_height);
const float z_near = 0.5f;
const float z_far = 10000.0f;
 
// camera (world position etc);
const float ground_height = 0.3f;
const float camera_x = -50.1f;
const float camera_y = 50.0f;
const float camera_speed = 15.0f;

const float camera_movement_speed = 4.0f;
const float camera_zoom_speed = 10.0f;
const int world_size = 150;

const float E = 2.71828183f;
const float pi = 3.14159265f;
const float eps = 0.0001f;

// simulation
const int particle_count = 6000000;
const int random_count =  particle_count * 100;
const int attractor_count = 8;

#define INVALID_SHADER_PROGRAM_ID 0



#include <iostream>
#include <fstream>
#include <string>
std::string file_to_string(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return "";
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }

    file.close();
    return content;
}


static void check_for_errors(int shader_id)
{
    GLint max_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> info_log(max_length);        
    if (info_log.size() > 0)
    {
        glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);
        std::string string_log = std::string(info_log.begin(), info_log.end());
        fmt::print("failed to compile shader in {}. GL errror: {}\n", __func__, string_log);
    }
    GLint shader_compiled = GL_FALSE; 
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &shader_compiled);

    //@FIXME(SMIA): uh... this should mos def not be deleting shaders.
    if (shader_compiled != GL_TRUE)
    {
        std::cerr << "huh?" << '\n';
        fmt::print("shader did not compile. bail!\n");
        glDeleteShader(shader_id); // Don't leak the shader.
        exit(1);
    }
}

static int create_shader_program(const char* vertex_path, const char* fragment_path)
{
    const uint32_t shader_program = glCreateProgram();

    int shader_program_id = INVALID_SHADER_PROGRAM_ID;

    int vertex_shader_id   = glCreateShader(GL_VERTEX_SHADER);
    int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    // compile vertex shader.
    std::string vertex_shader_src = file_to_string(vertex_path);
    const char* vertex_shader_c_str = vertex_shader_src.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_shader_c_str, NULL);
    glCompileShader(vertex_shader_id);
    check_for_errors(vertex_shader_id);

    // compile fragment shader.
    std::string fragment_shader_src = file_to_string(fragment_path);
    const char* fragment_shader_c_str = fragment_shader_src.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_shader_c_str, NULL);
    glCompileShader(fragment_shader_id);
    check_for_errors(fragment_shader_id);


    return shader_program_id;
}

static int compile_compute_shader(const char* compute_path)
{
    fmt::print("[warning] function {} not implemented yet! \n", __func__);
    return INVALID_SHADER_PROGRAM_ID;
}


// to get openGL debug info, you need a glfw version > 3.3 (4.5 should work)
// as well as a OPENGL_DEBUG_CONTEXT!
int main() {

    // note to self: do not call gl functions before glad is live.
    // window stuff.
    GLFWwindow* window = nullptr;

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

    int compute_shader = compile_compute_shader("");
    int shader_program = create_shader_program("shaders/color_shader.vert", "shaders/color_shader.frag");
    fmt::print("compute shader: {}\n", compute_shader);

    while (!glfwWindowShouldClose(window))
    {
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}