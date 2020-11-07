#include <spdlog/spdlog.h>
#include "engine/core/Core.hpp"
#include "engine/render/Render.hpp"

int main() {
    spdlog::info("Engine has been launched");
    spdlog::info(engine::render::echo(42));
    spdlog::info(engine::core::echo(42));
    spdlog::info("Engine has been shut down");
    return 0;
}