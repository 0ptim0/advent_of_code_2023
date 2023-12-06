CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

set(PROJ_NAME 5_If_you_give_a_seed_a_fertilizer)

set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
project(${PROJ_NAME})
include_directories(./)

file(GLOB SRC
    "main.cpp"
)

add_executable(${PROJ_NAME} ${SRC})
