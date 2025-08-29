cmake_minimum_required(VERSION 3.16)

project(SolarSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLOB all source files
file(GLOB RESOURCE_FILES "source/*.cpp" "source/*.h")

add_executable(${PROJECT_NAME} ${RESOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Vendor/Stb)

target_precompile_headers(${PROJECT_NAME} PRIVATE "source/PCH.h")

find_package(glfw3 CONFIG REQUIRED)
find_package(glew REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

# Post build command for copying resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources
						$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)