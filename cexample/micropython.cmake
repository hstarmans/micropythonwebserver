# Create an INTERFACE library for our C module.
add_library(usermod_cexample INTERFACE)

# Add our source files to the lib
target_sources(usermod_cexample INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/examplemodule.c
    ${CMAKE_CURRENT_LIST_DIR}/fomu-flash.c
    ${CMAKE_CURRENT_LIST_DIR}/fpga.c
    ${CMAKE_CURRENT_LIST_DIR}/ice40.c
    ${CMAKE_CURRENT_LIST_DIR}/rpi.c
    ${CMAKE_CURRENT_LIST_DIR}/spi.c
)

# Add the current directory as an include directory.
target_include_directories(usermod_cexample INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_cexample)
