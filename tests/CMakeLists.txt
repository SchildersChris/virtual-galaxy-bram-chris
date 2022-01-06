# -----------------------------------------------------------------------------
#  Testing setup
# -----------------------------------------------------------------------------

FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable(tests
    main.cpp
    math/matrix4x4_tests.cpp
    math/vector3_tests.cpp
)

target_compile_features(tests PRIVATE cxx_std_17)
target_link_libraries(tests PRIVATE virtual-galaxy Catch2::Catch2)

add_test(NAME matrix4x4_tests COMMAND tests)
add_test(NAME vector3_tests COMMAND tests)
