#include "math/vector2.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[VECTOR2] Should create", "[create]") {
    SECTION("Should create empty vector") {
        Vector2 v;

        REQUIRE(v.X == 0);
        REQUIRE(v.Y == 0);
    }

    SECTION("[VECTOR2] Should create vector") {
        float x = 10.f, y = 10.f, z = 10.f;

        Vector2 v {x, y};

        REQUIRE(v.X == x);
        REQUIRE(v.Y == y);
    }
}

TEST_CASE("[VECTOR2] Should handle operations correctly", "[operations]") {
    SECTION("Checks") {
        SECTION("Equal") {
            float x = 10.f, y = 10.f;

            Vector2 v1 {x, y};
            Vector2 v2 {x, y};

            REQUIRE(v1 == v2);
        }

        SECTION("Not equal") {
            float x = 10.f, y = 10.f;

            Vector2 v1 {x, y};
            Vector2 v2 {x + 1, y};

            REQUIRE(v1 != v2);
        }
    }

    SECTION("Add") {
        SECTION("Add vector") {
            float x = 10.f, y = 10.f;
            Vector2 v1 {x, y};
            Vector2 v2 {x, y};

            Vector2 res = v1 + v2;

            REQUIRE(res.X == x + x);
            REQUIRE(res.Y == y + y);
        }

        SECTION("Add float") {
            float x = 10.f, y = 10.f;
            float addVal = 3.f;
            Vector2 v1 {x, y};

            Vector2 res = v1 + 3;

            REQUIRE(res.X == x + addVal);
            REQUIRE(res.Y == y + addVal);
        }
    }

    SECTION("Subtract") {
        SECTION("Subtract vector") {
            float x = 10.f, y = 10.f;
            Vector2 v1 {x, y};
            Vector2 v2 {x, y};

            Vector2 res = v1 - v2;

            REQUIRE(res.X == x - x);
            REQUIRE(res.Y == y - y);
        }

        SECTION("Subtract float") {
            float x = 10.f, y = 10.f, z = 10.f;
            float subtractVal = 3.f;
            Vector2 v1 {x, y};

            Vector2 res = v1 - 3;

            REQUIRE(res.X == x - subtractVal);
            REQUIRE(res.Y == y - subtractVal);
        }
    }

    SECTION("Multiply") {
        SECTION("Multiply vector") {
            float x = 10.f, y = 10.f;
            Vector2 v1 {x, y};
            Vector2 v2 {x, y};

            Vector2 res = v1 * v2;

            REQUIRE(res.X == 100);
            REQUIRE(res.Y == 100);
        }

        SECTION("Multiply float") {
            float x = 10.f, y = 10.f;
            float mulVal = 3.f;
            Vector2 v1 {x, y};

            Vector2 res = v1 * mulVal;

            REQUIRE(res.X == x * mulVal);
            REQUIRE(res.Y == y * mulVal);
        }
    }

    SECTION("Divide") {
        SECTION("Divide vector") {
            float x = 10.f, y = 10.f;
            Vector2 v1 {x, y};
            Vector2 v2 {x, y};

            Vector2 res = v1 / v2;

            REQUIRE(res.X == x / x);
            REQUIRE(res.Y == y / y);
        }

        SECTION("Divide float") {
            float x = 10.f, y = 10.f;
            float divVal = 3.f;
            Vector2 v1 {x, y};

            Vector2 res = v1 / divVal;

            REQUIRE(res.X == x / divVal);
            REQUIRE(res.Y == y / divVal);
        }
    }
}
