#include "math/vector4.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[VECTOR4] Should create vector4", "[create]") {
    SECTION("Should create empty vector") {
        Vector4 v;

        REQUIRE(v.X == 0);
        REQUIRE(v.Y == 0);
        REQUIRE(v.Z == 0);
        REQUIRE(v.W == 0);
    }

    SECTION("Should create vector") {
        float x = 10.f, y = 10.f, z = 10.f, w = 10.f;

        Vector4 v {x, y, z, w};

        REQUIRE(v.X == x);
        REQUIRE(v.Y == y);
        REQUIRE(v.Z == z);
        REQUIRE(v.W == w);
    }
}

TEST_CASE("[VECTOR4] Should handle operations correctly", "[operations]") {
    SECTION("Checks") {
        SECTION("Equal") {
            float x = 10.f, y = 10.f, z = 10.f, w = 10.f;

            Vector4 v1 {x, y, z, w};
            Vector4 v2 {x, y, z, w};

            REQUIRE(v1 == v2);
        }

        SECTION("Not equal") {
            float x = 10.f, y = 10.f, z = 10.f, w = 10.f;

            Vector4 v1 {x, y, z, w};
            Vector4 v2 {x, y + 1, z, w};

            REQUIRE(v1 != v2);
        }
    }

    SECTION("Multiply") {
        SECTION("Multiply matrix") {
            float x = 10.f, y = 10.f, z = 10.f, w = 10.f;
            Vector4 vec {x, y, z, w};

            Matrix4x4 m {
                    2, 0, 0, 0,
                    0, 2, 0, 0,
                    0, 0, 2, 0,
                    0, 0, 0, 1,
            };

            Vector4 res = vec * m;

            REQUIRE(res.X == 20);
            REQUIRE(res.Y == 20);
            REQUIRE(res.Z == 20);
            REQUIRE(res.W == 10);
        }
    }
}
TEST_CASE("[VECTOR4] To vector3", "[to vector3]") {
    Vector4 vec {1, 1, 1, 1};

    auto res = vec.toVector3();

    REQUIRE(typeid(res) == typeid(Vector3));
}
