CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

set(PROJ_NAME 4_Scratchcards)

set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
project(${PROJ_NAME})
include_directories(./)

file(GLOB SRC
    "main.cpp"
)

add_executable(${PROJ_NAME} ${SRC})
