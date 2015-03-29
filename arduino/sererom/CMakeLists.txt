set(ARDUINO_DEFAULT_BOARD uno) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

generate_arduino_firmware(sererom
    SRCS sererom.cpp
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l)
