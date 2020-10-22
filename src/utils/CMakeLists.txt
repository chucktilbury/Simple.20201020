
project(utils)

add_library(utils STATIC
    errors.c
    stack.c
    queue.c
    #linked_lists.c
    hash_table.c
    #xxhash.c
    configure.c
    lists.c
    memory.c
    misc.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}/../parser
)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-g" "-D_DEBUGGING")
