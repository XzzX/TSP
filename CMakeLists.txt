cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set (CMAKE_CXX_STANDARD 14)

project(TravellingSalesmanProblem)
add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/algorithm/Greedy.cpp"
    "src/algorithm/InOrder.cpp"
    "src/util/random.cpp"
    "src/visualization/Display.cpp"
    "src/visualization/Input.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "src")
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra)

find_package (SFML 2.3 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

