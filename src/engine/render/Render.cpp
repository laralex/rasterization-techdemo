#include "Render.hpp"
#include "engine/core/Core.hpp"

//#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

namespace engine::render 
{
    
ENGINE_API std::int32_t echo(std::int32_t message) {
    auto answer = engine::core::echo(message);
    return answer;
}

ENGINE_API std::int32_t initialize_opengl() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        spdlog::info("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::info("Failed to initialize GLAD");
        return -1;
    } 

    glfwTerminate();
    return 0;
}

} // namespace engine::render

