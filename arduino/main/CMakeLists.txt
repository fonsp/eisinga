set(ARDUINO_DEFAULT_BOARD uno) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

generate_arduino_library(main_lib
    SRCS  main_lib.cpp
    HDRS  main_lib.h)

generate_arduino_firmware(main
    SRCS main.cpp
    LIBS main_lib
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l)
