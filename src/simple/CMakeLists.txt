
project(simple)

add_executable(${PROJECT_NAME}
    simple.c
    #globals.c
)

target_link_libraries(${PROJECT_NAME}
    parser
    configure
    parser_support
    #expressions
    utils
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}/../parser
)

target_compile_options(${PROJECT_NAME} PRIVATE
    "-Wall" "-Wextra"
    "$<$<CONFIG:DEBUG>:-O0;-g;-D_DEBUGGING>"
    "$<$<CONFIG:RELEASE>:-Ofast>"
)
