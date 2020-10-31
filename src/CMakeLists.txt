###############################################################################
# Main source code directory.
###############################################################################

# build the libraries
add_subdirectory(parser)
add_subdirectory(parser_support)
add_subdirectory(utils)
add_subdirectory(configure)


# build the main program
add_subdirectory(simple)
