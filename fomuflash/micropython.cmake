# Create an INTERFACE library for our C module.
add_library(fomuflash INTERFACE)

# Add our source files to the lib
target_sources(fomuflash INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/pythonwrap.c
    ${CMAKE_CURRENT_LIST_DIR}/fomu-flash.c
    ${CMAKE_CURRENT_LIST_DIR}/fpga.c
    ${CMAKE_CURRENT_LIST_DIR}/ice40.c
    ${CMAKE_CURRENT_LIST_DIR}/rpi.c
    ${CMAKE_CURRENT_LIST_DIR}/spi.c
)

# Add the current directory as an include directory.
target_include_directories(fomuflash INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE fomuflash)
