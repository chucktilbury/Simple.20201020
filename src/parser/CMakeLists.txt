
project(parser)

include_directories(${PROJECT_SOURCE_DIR}/../include)

set(LEX_FILE      ${CMAKE_CURRENT_SOURCE_DIR}/scanner.l)
set(LEX_C_SOURCE  ${CMAKE_CURRENT_SOURCE_DIR}/scanner.c)
set(LEX_H         ${PROJECT_INCLUDE_DIRECTORY}/scanner.h)
set(YACC_FILE     ${CMAKE_CURRENT_SOURCE_DIR}/parser.y)
set(YACC_C_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/parser.c)
set(YACC_H        ${PROJECT_INCLUDE_DIRECTORY}/parser.h)

#add_custom_target(unionLexHeader DEPENDS ${LEX_H})
add_custom_command(OUTPUT ${LEX_C_SOURCE}
        DEPENDS ${LEX_FILE}
        PRE_BUILD
        COMMAND flex -o scanner.c scanner.l
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#add_custom_target(unionYaccHeader DEPENDS ${YACC_H} ${YACC_C_SOURCE} parser.output)
add_custom_command(OUTPUT ${YACC_C_SOURCE} ${YACC_H}
        DEPENDS ${YACC_FILE}
        PRE_BUILD
        COMMAND bison --report=lookahead -tvdo parser.c parser.y
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC
    parser.c
    scanner.c
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}/../parser_support
)

target_compile_options(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:DEBUG>:-O0;-g;-D_DEBUGGING>"
    "$<$<CONFIG:RELEASE>:-Ofast>"
)

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.output"
)

#set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../lib")
