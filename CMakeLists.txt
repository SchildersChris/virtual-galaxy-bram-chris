# -----------------------------------------------------------------------------
#  Project setup
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.12...3.21)

project(
  cmake-template
  VERSION 0.1.0
  DESCRIPTION "A CMake project template"
  HOMEPAGE_URL "https://github.com/SchildersChris/cmake-template"
  LANGUAGES CXX)

# Only execute these settings when the project is not included through `add_subdirectory`
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(cmake/default.cmake)
  include(cmake/ide.cmake)

  include(CTest)

  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/fetchContent_makeAvailable.cmake)
endif()

find_package(Boost REQUIRED)

FetchContent_Declare(
  fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 5.3.0)
FetchContent_MakeAvailable(fmtlib)

add_subdirectory(src)

add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
