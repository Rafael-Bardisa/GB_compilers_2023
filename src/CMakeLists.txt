# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${COMPILERS_PROJECT_GB_SOURCE_DIR}/headers/*.h")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${COMPILERS_PROJECT_GB_SOURCE_DIR}/src/*.c")

message(STATUS "building from source dir ${COMPILERS_PROJECT_GB_SOURCE_DIR}")

# Make an automatic library - will be static or dynamic based on user setting
message(STATUS "Creating library from files ${HEADER_LIST}")
message(STATUS "Creating library from files ${SOURCE_LIST}")

add_library(gb_lib ${SOURCE_LIST} ${HEADER_LIST} common.c)

# We need this directory, and users of our library will need it too
target_include_directories(gb_lib PUBLIC ../headers)


set_property(TARGET gb_lib PROPERTY C_STANDARD 99)

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/headers"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
