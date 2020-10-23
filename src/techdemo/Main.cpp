#include <iostream>
#include <engine/core/Core.hpp>
#include <engine/render/Render.hpp>

int main() {
    std::cout << "Engine has been launched" << std::endl;
    std::cout << engine::render::echo(42) << std::endl;
    std::cout << engine::core::echo(42) << std::endl;
    std::cout << "Engine has been shut down" << std::endl;
    return 0;
}