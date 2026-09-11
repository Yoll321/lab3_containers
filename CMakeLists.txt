cmake_minimum_required(VERSION 3.23)

project(containers)

add_executable(containers
    src/main.cpp)

target_include_directories(containers PRIVATE
    include)