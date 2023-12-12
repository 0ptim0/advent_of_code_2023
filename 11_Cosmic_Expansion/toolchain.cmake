cmake_minimum_required(VERSION 3.6)

set(TOOLCHAIN Linux)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86)
set(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_C_COMPILER_WORKS   TRUE)
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

set(CMAKE_C_COMPILER   /bin/gcc)
set(CMAKE_CXX_COMPILER /bin/g++)
set(CMAKE_ASM_COMPILER /bin/gcc)
set(CMAKE_SIZE         /bin/size)
set(CMAKE_OBJCOPY      /bin/objcopy)
set(CMAKE_OBJDUMP      /bin/objdump)

string(CONCAT COMPILER_FLAGS
    "${MCU_FLAGS} "
    "-Werror -pedantic-errors "
    "-Wall -Wextra "
    "-Wpedantic "
    "-Wcast-align "
    "-Wcast-qual "
    "-Wduplicated-branches "
    "-Wduplicated-cond "
    "-Wfloat-equal "
    "-Wlogical-op "
    "-Wredundant-decls "
    "-Wsign-conversion "
    "-Wconversion "
    "-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Wno-missing-braces "
)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3 ${COMPILER_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG ${COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 ${COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ${COMPILER_FLAGS}")
