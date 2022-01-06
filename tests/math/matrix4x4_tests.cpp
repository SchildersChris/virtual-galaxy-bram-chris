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
    Matrix4x4 m1 {
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
    };

    Matrix4x4 m2 {
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
    };

    SECTION("Multiply") {
        Matrix4x4 m = m1 * m2;

        Matrix4x4 val {
            16, 16, 16, 16,
            16, 16, 16, 16,
            16, 16, 16, 16,
            16, 16, 16, 16
        };

        REQUIRE(m == val);
    }
}

TEST_CASE("Should correctly rotate vector4", "[multiply]") {
    float x = 10, y = 5, z = 2;
    auto rotate = Matrix4x4::rotation(x, y, z);

    auto v = Vector4 { 1, 1, 1, 1 };

//    SECTION("Create") {
//        REQUIRE(rotate(3, 0) == x);
//        REQUIRE(rotate(3, 1) == y);
//        REQUIRE(rotate(3, 2) == z);
//    }

    // TODO: Not sure how to validate the rotation matrix.
    SECTION("Multiply") {
        auto vs = v * rotate;

        REQUIRE(vs.X == x);
        REQUIRE(vs.Y == y);
        REQUIRE(vs.Z == z);
    }
}

TEST_CASE("Should correctly translate vector4", "[multiply]") {
    float x = -10, y = -10, z = -10;
    auto translate = Matrix4x4::translation(x, y, z);

    auto v = Vector4 { 10, 10, 10, 1 };

    SECTION("Create") {
        REQUIRE(translate(3, 0) == x);
        REQUIRE(translate(3, 1) == y);
        REQUIRE(translate(3, 2) == z);
    }

    // TODO: Not sure how to validate the rotation matrix.
    SECTION("Multiply") {
        auto vs = v * translate;

        REQUIRE(vs.X == 0);
        REQUIRE(vs.Y == 0);
        REQUIRE(vs.Z == 0);
    }
}

TEST_CASE("Should correctly check if matrices are equal", "[equal]") {
    Matrix4x4 m1 {
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
    };

    Matrix4x4 m2 {
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
    };

    SECTION("Equal") {
        REQUIRE(m1 == m2);
    }
}


TEST_CASE("Should correctly check if matrices are NOT equal", "[equal]") {
    Matrix4x4 m1 {
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
    };

    Matrix4x4 m2 {
            2, 2, 2, 2,
            2, 2, 3, 2,
            2, 2, 2, 2,
            2, 2, 2, 2,
    };

    SECTION("Not equal") {
        REQUIRE(m1 != m2);
    }
}
