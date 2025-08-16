cmake_minimum_required(VERSION 3.14)

project(SolarSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLOB all source files
file(GLOB RESOURCE_FILES "source/*.cpp" "source/*.h")

add_executable(${PROJECT_NAME} ${RESOURCE_FILES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glew REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)