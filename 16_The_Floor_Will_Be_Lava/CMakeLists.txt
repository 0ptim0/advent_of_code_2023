CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

set(PROJ_NAME 16_The_Floor_Will_Be_Lava)

set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
project(${PROJ_NAME})
include_directories(./)

file(GLOB SRC
    "main.cpp"
)

add_executable(${PROJ_NAME} ${SRC})
