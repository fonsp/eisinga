#=============================================================================#
# Author: QueezyTheGreat                                                      #
# Date:   26.04.2011                                                          #
#                                                                             #
# Description: Arduino CMake example                                          #
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#

link_directories(lib)
set(Wire_RECURSE True)

project(ArduinoExample C CXX)
set(Wire_RECURSE True)
#print_board_list()
#print_programmer_list()

add_subdirectory(main)
add_subdirectory(sererom)
