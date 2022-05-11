cmake_minimum_required(VERSION 3.10)

message(STATUS "The CMAKE_VERSION is ${CMAKE_VERSION}.")

project( filemapping )

add_executable(${PROJECT_NAME}
	main.cpp
	filemapping.cpp
	filemapping.h
)

