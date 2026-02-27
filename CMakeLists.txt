cmake_minimum_required(VERSION 3.15)
project(CommandAdvisor VERSION 2.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for better warnings and optimization
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -O2
    )
elseif(MSVC)
    add_compile_options(
        /W4
        /WX
        /O2
    )
endif()

# Main executable
add_executable(advisor advisor.cpp)

# Link filesystem library if needed (for older compilers)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(advisor stdc++fs)
endif()

# Installation rules
install(TARGETS advisor
    RUNTIME DESTINATION bin
)

# Print build information
message(STATUS "")
message(STATUS "═══════════════════════════════════════════════════════")
message(STATUS "  Command Advisor v${PROJECT_VERSION}")
message(STATUS "═══════════════════════════════════════════════════════")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "═══════════════════════════════════════════════════════")
message(STATUS "")
