cmake_minimum_required(VERSION 3.5)
project(project2 VERSION 0.1.0)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 11)

# Add executable target for main.cpp
add_executable(MyExecutable src/main.cpp)


