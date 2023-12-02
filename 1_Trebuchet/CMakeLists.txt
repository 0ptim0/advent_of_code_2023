CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

set(PROJ_NAME Trebuchet)

set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
project(${PROJ_NAME})
include_directories(./)

file(GLOB SRC
    "main.cpp"
)

add_executable(${PROJ_NAME} ${SRC})

target_link_libraries(${PROJ_NAME}
    "-lcurl"
)
