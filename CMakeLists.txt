# -----------------------------------------------------------------------------
#  Project setup
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14...3.21)

project(
  virtual-galaxy
  VERSION 0.1.0
  DESCRIPTION "Avans Hogeschool - Linear Algebra assessment"
  HOMEPAGE_URL "https://github.com/SchildersChris/cmake-template"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(cmake/default.cmake)
  include(cmake/ide.cmake)
  include(cmake/definitions.cmake)
endif()

include(FetchContent)

add_subdirectory(src)
add_subdirectory(app)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
  include(CTest)
  add_subdirectory(tests)
endif()
