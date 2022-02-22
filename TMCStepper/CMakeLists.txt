# Simple makefile
cmake_minimum_required(VERSION 3.3)
# pybind requires c14++, not needed for TMCStepper
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(TMCStepper)

#  bcm2835 library for raspberry
add_definitions(-Wall -Dbcm2835)


#Bring the headers, deprecated
include_directories(src
                   src/source)

# sources should be added manually
set(LIB_SOURCES 
            ${PROJECT_SOURCE_DIR}/usercmodule/TMCStepper/micropython/pythonwrapp.c)
            #${PROJECT_SOURCE_DIR}/src/source/bcm2835_spi.cpp
            #${PROJECT_SOURCE_DIR}/src/source/bcm2835_stream.cpp
            #${PROJECT_SOURCE_DIR}/src/source/CHOPCONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/COOLCONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/DRV_CONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/DRV_STATUS.cpp
            #${PROJECT_SOURCE_DIR}/src/source/DRVCONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/DRVCTRL.cpp
            #${PROJECT_SOURCE_DIR}/src/source/DRVSTATUS.cpp
            #${PROJECT_SOURCE_DIR}/src/source/ENCMODE.cpp
            #${PROJECT_SOURCE_DIR}/src/source/GCONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/IHOLD_IRUN.cpp
            #${PROJECT_SOURCE_DIR}/src/source/PWMCONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/RAMP_STAT.cpp
            #${PROJECT_SOURCE_DIR}/src/source/SERIAL_SWITCH.cpp
            #${PROJECT_SOURCE_DIR}/src/source/SGCSCONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/SHORT_CONF.cpp
            #${PROJECT_SOURCE_DIR}/src/source/SMARTEN.cpp
            #${PROJECT_SOURCE_DIR}/src/source/SW_MODE.cpp
            #${PROJECT_SOURCE_DIR}/src/source/SW_SPI.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC2130Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC2160Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC2208Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC2209Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC2660Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC5130Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMC5160Stepper.cpp
            #${PROJECT_SOURCE_DIR}/src/source/TMCStepper.cpp)

# this code can be used to build c++ examples
# compilation output is placed in  binary folder

### PART USED FOR EXAMPLES
# library is written to build folder
# add_library( TMC2130Lib ${LIB_SOURCES})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set(TARGETS ${PROJECT_SOURCE_DIR}/examples/Simple/Simple.cpp)
# 	    ${PROJECT_SOURCE_DIR}/examples/testyconnection.cpp
# 	    ${PROJECT_SOURCE_DIR}/examples/testxconnection.cpp
# 	    ${PROJECT_SOURCE_DIR}/examples/homex.cpp)

#foreach( target ${TARGETS})
#     get_filename_component(targetname ${target} NAME)
#     string( REPLACE ".cpp" "" targetname ${targetname} )
#     add_executable( ${targetname} ${target}) 
#     target_link_libraries( ${targetname} TMC2130Lib bcm2835)
#endforeach( target ${TARGETS})

### END PART USED FOR EXAMPLES

#### PART USED FOR PYTHON LIBRARY

# build the python module
add_subdirectory(${PROJECT_SOURCE_DIR}/python/pybind11)

pybind11_add_module(steppers ${PROJECT_SOURCE_DIR}/python/src/main.cpp ${LIB_SOURCES})
target_link_libraries(steppers PRIVATE bcm2835)

## EN PART USED FOR PYTHON LIBRARY