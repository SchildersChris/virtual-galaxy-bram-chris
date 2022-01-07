#include "math/vector3.hpp"
#include "math/vector4.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[VECTOR3] Should create vector3", "[create]") {
    SECTION("Should create empty vector") {
        Vector3 v;

        REQUIRE(v.X == 0);
        REQUIRE(v.Y == 0);
        REQUIRE(v.Z == 0);
    }

    SECTION("Should create vector") {
        float x = 10.f, y = 10.f, z = 10.f;

        Vector3 v {x, y, z};

        REQUIRE(v.X == x);
        REQUIRE(v.Y == y);
        REQUIRE(v.Z == z);
    }
}

TEST_CASE("[VECTOR3] Should handle operations correctly", "[operations]") {
    SECTION("Checks") {
        SECTION("Equal") {
            float x = 10.f, y = 10.f, z = 10.f;

            Vector3 v1 {x, y, z};
            Vector3 v2 {x, y, z};

            REQUIRE(v1 == v2);
        }

        SECTION("Not equal") {
            float x = 10.f, y = 10.f, z = 10.f;

            Vector3 v1 {x, y, z};
            Vector3 v2 {x + 1, y, z};

            REQUIRE(v1 != v2);
        }
    }

    SECTION("Add") {
        SECTION("Add vector") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 v1 {x, y, z};
            Vector3 v2 {x, y, z};

            Vector3 res = v1 + v2;

            REQUIRE(res.X == x + x);
            REQUIRE(res.Y == y + y);
            REQUIRE(res.Z == z + z);
        }

        SECTION("Add float") {
            float x = 10.f, y = 10.f, z = 10.f;
            float addVal = 3.f;
            Vector3 v1 {x, y, z};

            Vector3 res = v1 + 3;

            REQUIRE(res.X == x + addVal);
            REQUIRE(res.Y == y + addVal);
            REQUIRE(res.Z == z + addVal);
        }

        SECTION("Add and assign vector") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 v1 {x, y, z};
            Vector3 v2 {x, y, z};

            v1 += v2;

            REQUIRE(v1.X == x + x);
            REQUIRE(v1.Y == y + y);
            REQUIRE(v1.Z == z + z);
        }
    }

    SECTION("Subtract") {
        SECTION("Subtract vector") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 v1 {x, y, z};
            Vector3 v2 {x, y, z};

            Vector3 res = v1 - v2;

            REQUIRE(res.X == x - x);
            REQUIRE(res.Y == y - y);
            REQUIRE(res.Z == z - z);
        }

        SECTION("Subtract float") {
            float x = 10.f, y = 10.f, z = 10.f;
            float subtractVal = 3.f;
            Vector3 v1 {x, y, z};

            Vector3 res = v1 - 3;

            REQUIRE(res.X == x - subtractVal);
            REQUIRE(res.Y == y - subtractVal);
            REQUIRE(res.Z == z - subtractVal);
        }

        SECTION("Subtract inverse") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 v1 {x, y, z};

            Vector3 res = -v1;

            REQUIRE(res.X == x * -1);
            REQUIRE(res.Y == y * -1);
            REQUIRE(res.Z == z * -1);
        }
    }

    SECTION("Multiply") {
        SECTION("Multiply vector") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 v1 {x, y, z};
            Vector3 v2 {x, y, z};

            Vector3 res = v1 * v2;

            REQUIRE(res.X == 100);
            REQUIRE(res.Y == 100);
            REQUIRE(res.Z == 100);
        }

        SECTION("Multiply float") {
            float x = 10.f, y = 10.f, z = 10.f;
            float mulVal = 3.f;
            Vector3 v1 {x, y, z};

            Vector3 res = v1 * mulVal;

            REQUIRE(res.X == x * mulVal);
            REQUIRE(res.Y == y * mulVal);
            REQUIRE(res.Z == z * mulVal);
        }

        SECTION("Multiply matrix") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 vec {x, y, z};

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
        }
    }

    SECTION("Divide") {
        SECTION("Divide vector") {
            float x = 10.f, y = 10.f, z = 10.f;
            Vector3 v1 {x, y, z};
            Vector3 v2 {x, y, z};

            Vector3 res = v1 / v2;

            REQUIRE(res.X == x / x);
            REQUIRE(res.Y == y / y);
            REQUIRE(res.Z == z / z);
        }

        SECTION("Divide float") {
            float x = 10.f, y = 10.f, z = 10.f;
            float divVal = 3.f;
            Vector3 v1 {x, y, z};

            Vector3 res = v1 / divVal;

            REQUIRE(res.X == x / divVal);
            REQUIRE(res.Y == y / divVal);
            REQUIRE(res.Z == z / divVal);
        }
    }
}

TEST_CASE("[VECTOR3] Dot product", "[dot product]") {
    Vector3 vec1 {2, 4, 1};
    Vector3 vec2 {4, 1, 1};

    auto res = vec1.dot(vec2);

    REQUIRE(res == 13);
}

TEST_CASE("[VECTOR3] Cross product", "[cross product]") {
    Vector3 vec1 {2, 4, 1};
    Vector3 vec2 {4, 1, 1};

    auto res = vec1.cross(vec2);

    REQUIRE(res.X == 3);
    REQUIRE(res.Y == 2);
    REQUIRE(res.Z == -14);
}

TEST_CASE("[VECTOR3] Length", "[length]") {
    Vector3 vec1 {2, 4, 1};

    auto res = vec1.length();

    REQUIRE(fabs(res) == fabs(4.582575798f));
}

TEST_CASE("[VECTOR3] Normalize", "[normalize]") {
    Vector3 vec1 {1, 1, 1};
    Vector3 vec2 {10, 10, 10};

    auto res1 = vec1.normalize();
    auto res2 = vec2.normalize();

    REQUIRE(res1.X == 0.5773502691896257f);
    REQUIRE(res1.Y == 0.5773502691896257f);
    REQUIRE(res1.Z == 0.5773502691896257f);

    REQUIRE(res2.X == 0.5773502691896257f);
    REQUIRE(res2.Y == 0.5773502691896257f);
    REQUIRE(res2.Z == 0.5773502691896257f);
}

TEST_CASE("[VECTOR3] Cos", "[cos]") {
    Vector3 vec1 {2, 4, 1};
    Vector3 vec2 {4, 1, 1};

    auto res = vec1.cos(vec2);

    REQUIRE(res == 12.0356607f);
}

TEST_CASE("[VECTOR3] To vector2", "[to vector2]") {
    Vector3 vec {1, 1, 1};

    auto res = vec.toVector2();

    REQUIRE(typeid(res) == typeid(Vector2));
}
