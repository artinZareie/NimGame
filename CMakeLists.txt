cmake_minimum_required(VERSION 3.25.0)
project(NimGame)

# Define sources and headers directory
set(SOURCES src/main.c src/Constants.c src/Screen.c src/Game.c src/Utils.c src/Computer.c)

add_executable(NimGame ${SOURCES})


# Import libraries
include_directories(${CMAKE_SOURCE_DIR}/headers)
