###############################################################################
# CMakeLists.txt

# Set the minimum required CMake version.
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Set the project name.
project(MyProject)

# Add default compile flags.
add_compile_options("-std=c++14")

# Pull in external project support.
include(ExternalProject)

# Declare configuration options.
option(BUILD_DOCS "Build documentation" ON)
option(BUILD_SAMPLES "Build samples" ON)
option(BUILD_TESTS "Build unit tests" ON)

# Build external dependencies.
add_subdirectory(ext)

# Add the projects public include directory to the include path.
include_directories(include)

# Build the lib subdirectory.
add_subdirectory(lib)
add_subdirectory(tools)

# Optionally build documentation.
if (BUILD_DOCS)
  add_subdirectory(doc)
endif()

# Optionally build unit tests.
if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

# Optionally build samples.
if (BUILD_SAMPLES)
  add_subdirectory(samples)
endif()
