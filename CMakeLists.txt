cmake_minimum_required(VERSION 3.24)
project(COMPILERS_PROJECT_GB
        VERSION 0.1
        DESCRIPTION "Lexer program for a subset of C"
        LANGUAGES C)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(CTest)

endif()

if (NO_FMT)
    add_definitions(-DNO_FMT=1)
endif (NO_FMT)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(test)
endif()
