
project(semantics)

add_library(${PROJECT_NAME} STATIC
    validate_expr.c
    expr_arith.c
    expr_compare.c
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
