cmake_minimum_required(VERSION 3.19)

# Set project properties
set(PROJECT_NAME bimap)
set(PROJECT_VERSION_SEMANTIC 1.0.0)
set(PROJECT_VERSION_CPP_MIN 11)

# Set project options
# Options availables for external project start with "EXT_OPT_BIMAP_", those options can be use in top CMakeFiles.
# All options are disabled by default.
# List of available options :
# - No available options

# Set project configuration
project(${PROJECT_NAME} LANGUAGES CXX)
project(${PROJECT_NAME} VERSION "${PROJECT_VERSION_SEMANTIC}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set C++ standard to use
if(DEFINED CMAKE_CXX_STANDARD)
    if(${CMAKE_CXX_STANDARD} LESS ${PROJECT_VERSION_CPP_MIN})
        message(FATAL_ERROR "Project ${PROJECT_NAME} require at least C++ standard ${PROJECT_VERSION_CPP_MIN}")
    endif()
else()
    set(CMAKE_CXX_STANDARD ${PROJECT_VERSION_CPP_MIN})
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

# Set needed packages
## Example: find_package(nlohmann_json 3.11.3 REQUIRED)

# Configure file project - File containing macro that can be used in project
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

# Manage library files
set(PROJECT_HEADERS
    config.h
    bimapglobal.h

    bimap.h
)

set(PROJECT_SOURCES

)

set(PROJECT_RSC

)

set(PROJECT_FILES ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_RSC})

# Platform dependant stuff
# Windows (for both x86/x64)
if(WIN32)

endif()

# MacOS (for both x86/x64)
if(UNIX AND APPLE)

endif()

# Linux, BSD, Solaris, Minix (for both x86/x64)
if(UNIX AND NOT APPLE)

endif()

# Add files to the library
add_library(${PROJECT_NAME} INTERFACE ${PROJECT_FILES})

# Set version of library
set_target_properties(${PROJECT_NAME} PROPERTIES
                        VERSION ${PROJECT_VERSION}
                        SOVERSION ${PROJECT_VERSION_MAJOR})

# Link needed libraries
## No library to link

# Compile needed definitions
target_compile_definitions(${PROJECT_NAME} INTERFACE BIMAP_LIB)

# Definition which depends on options
# Ex :
# if(EXT_OPT_BIMAP_XYZ)
#   target_compile_definitions(${PROJECT_NAME} INTERFACE BIMAP_ENABLE_XYZ)
# endif()

# Directories to includes
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})