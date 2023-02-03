add_executable(gb_project main.c main.h)
set_property(TARGET gb_project PROPERTY C_STANDARD 99)

target_link_libraries(gb_project PRIVATE gb_lib)
