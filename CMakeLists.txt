cmake_minimum_required(VERSION 3.27)
project(par_prog_2)

set(CMAKE_CXX_STANDARD 23)

add_executable(par_prog_2
        parProg2.cpp
        Matrix.cpp
        FileWriter.cpp)

# For CMake < 3.9, we need to make the target ourselves
if(NOT TARGET OpenMP::OpenMP_CXX)
    find_package(Threads REQUIRED)
    add_library(OpenMP::OpenMP_CXX IMPORTED INTERFACE)
    set_property(TARGET OpenMP::OpenMP_CXX
            PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
    # Only works if the same flag is passed to the linker; use CMake 3.9+ otherwise (Intel, AppleClang)
    set_property(TARGET OpenMP::OpenMP_CXX
            PROPERTY INTERFACE_LINK_LIBRARIES ${OpenMP_CXX_FLAGS} Threads::Threads)

endif()
target_link_libraries(par_prog_2 PUBLIC OpenMP::OpenMP_CXX)
