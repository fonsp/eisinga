set(ARDUINO_DEFAULT_BOARD nano328) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0) # Default Port, when not specified

generate_arduino_firmware(sererom
    SRCS sererom.cpp
    PORT /dev/ttyUSB0
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l
    BOARD nano328)
