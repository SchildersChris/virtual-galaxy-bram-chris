#include "math/matrix4x4.hpp"
#include "math/vector4.hpp"

#include <catch2/catch.hpp>

TEST_CASE("Should create identity matrix", "[identity]") {
    auto identity = Matrix4x4::identity();

    REQUIRE(identity(0, 0) == 1);
    REQUIRE(identity(1, 1) == 1);
    REQUIRE(identity(2, 2) == 1);
    REQUIRE(identity(3, 3) == 1);
}

TEST_CASE("Should create translation matrix", "[translation]") {
    float x = 10, y = 5, z = 2;
    auto translation = Matrix4x4::translation(x, y, z);

    SECTION("Create") {
        REQUIRE(translation(3, 0) == x);
        REQUIRE(translation(3, 1) == y);
        REQUIRE(translation(3, 2) == z);
    }
}

TEST_CASE("Should correctly scale vector4", "[scale]") {
    float x = 10, y = 5, z = 2;
    auto scale = Matrix4x4::scale(x, y, z);

    auto v = Vector4 { 1, 1, 1, 1 };

    SECTION("Create") {
        REQUIRE(scale(0, 0) == x);
        REQUIRE(scale(1, 1) == y);
        REQUIRE(scale(2, 2) == z);
    }

    SECTION("Multiply") {
        auto vs = v * scale;

        REQUIRE(vs.X == x);
        REQUIRE(vs.Y == y);
        REQUIRE(vs.Z == z);
    }
}

TEST_CASE("Should correctly multiply matrices", "[multiply]") {
    float x = 10, y = 5, z = 2;
    auto scale = Matrix4x4::scale(x, y, z);

    auto v = Vector4 { 1, 1, 1, 1 };

    Matrix4x4 m = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };

    SECTION("Create") {
        REQUIRE(scale(0, 0) == x);
        REQUIRE(scale(1, 1) == y);
        REQUIRE(scale(2, 2) == z);
    }

    SECTION("Multiply") {
        auto vs = v * scale;

        REQUIRE(vs.X == x);
        REQUIRE(vs.Y == y);
        REQUIRE(vs.Z == z);
    }
}
