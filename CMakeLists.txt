cmake_minimum_required(VERSION 3.25.0)
project(NimGame)

# Define sources and headers directory
set(SOURCES src/main.c)

add_executable(NimGame ${SOURCES})
target_link_directories(NimGame PRIVATE ${CMAKE_SOURCE_DIR}/headers)
