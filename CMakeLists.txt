cmake_minimum_required(VERSION 3.25.0)
project(NimGame)

# Define sources and headers directory
set(SOURCES src/main.c src/Constants.c src/Screen.c src/Game.c src/Utils.c src/Computer.c)

add_executable(NimGame ${SOURCES})

# Check if SQLite and SDL are installed, if not, sorry, please install them.
find_package(SQLite3 REQUIRED)

# Import libraries
include_directories(${CMAKE_SOURCE_DIR}/headers ${SQLite3_INCLUDE_DIR})

target_link_libraries(NimGame PRIVATE ${SQLite3_LIBRARIES})
