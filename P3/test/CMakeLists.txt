# Tests need to be added as executables first
add_executable(testlib testlib.c)

# I'm using C++17 in the test
set_property(TARGET testlib PROPERTY C_STANDARD 99)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(testlib PRIVATE gb_lib)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testlibtest COMMAND testlib) # Command can be a target
