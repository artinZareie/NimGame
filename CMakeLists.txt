cmake_minimum_required(VERSION 3.25.0)
project(NimGame)

# Define sources and headers directory
set(SOURCES src/main.c)

add_executable(NimGame ${SOURCES})

# Check if SQLite and SDL are installed, if not, sorry, please install them.
find_package(SQLite3 REQUIRED)
find_package(SDL2 REQUIRED)

# Import libraries
include_directories(${CMAKE_SOURCE_DIR}/headers ${SDL2_INCLUDE_DIRS}
                    ${SQLite3_INCLUDE_DIR})

target_link_libraries(NimGame PRIVATE ${SDL2_LIBRARIES} ${SQLite3_LIBRARIES})
