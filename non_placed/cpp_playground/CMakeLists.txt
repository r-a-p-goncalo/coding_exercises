cmake_minimum_required(VERSION 4.3)
project(cpp_playground)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_playground main.cpp
        person.h
        person.cpp
        device_play.cpp
        device_play.h
        device_play.h)
