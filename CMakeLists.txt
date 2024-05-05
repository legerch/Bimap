cmake_minimum_required(VERSION 3.19)
project(BimapMain LANGUAGES CXX)

# Set C++ standard to use
## Don't explicitly set C++ standard to use, let library use
## minimal standard version set
## set(CMAKE_CXX_STANDARD 17)

# Find architecture property
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PROJECT_ARCH_TARGET "amd64")    # x64
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PROJECT_ARCH_TARGET "i386")     # x86
else()
    message(FATAL_ERROR "Unkwnown architecture, CMake will exit.")
endif()

# Defines options of project
# Ex : set(EXT_OPT_LIBRARY_XYZ 0)

# Export generated binaries
if(NOT PROJECT_BUILD_OUTPUT)
    set(PROJECT_BUILD_OUTPUT ${CMAKE_SOURCE_DIR}/build/output/${PROJECT_ARCH_TARGET}/${CMAKE_BUILD_TYPE})

    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BUILD_OUTPUT}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/bin)
endif()

# Run subdirectory routine
add_subdirectory(lib)
add_subdirectory(tests)
