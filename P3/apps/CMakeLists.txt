add_executable(gb_project main.c main.h)
set_property(TARGET gb_project PROPERTY C_STANDARD 99)

target_link_libraries(gb_project PRIVATE gb_lib)

add_custom_command(TARGET gb_project POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources/
        $<TARGET_FILE_DIR:gb_project>/resources/)