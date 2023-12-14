CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

set(PROJ_NAME 14_Parabolic_Reflector_Dish)

set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
project(${PROJ_NAME})
include_directories(./)

file(GLOB SRC
    "main.cpp"
)

add_executable(${PROJ_NAME} ${SRC})
