#include <gtest/gtest.h>
#include "engine/render/Render.hpp"

GTEST_TEST(Example, Echo)
{
    auto res = engine::render::echo(42);
    ASSERT_EQ(res, 42);
}

GTEST_TEST(Render, OpenGL)
{
    auto succeeded = engine::render::initialize_opengl();
    ASSERT_EQ(succeeded, 0);
}