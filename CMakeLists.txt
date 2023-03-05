cmake_minimum_required(VERSION 3.16)
project(RandoMealPlanner)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/RandoMealPlanner.cpp
    ${CMAKE_SOURCE_DIR}/src/MealItems.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/src
)



