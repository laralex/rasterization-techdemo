#include "Render.hpp"
#include "engine/core/Core.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace engine::render {
    std::int32_t echo(std::int32_t message) {
        auto answer = engine::core::echo(message);
        return answer;
    }
}

