cmake_minimum_required(VERSION 3.16)
project(RandomKingOnChessboard_Project LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
GIT_REPOSITORY https://github.com/SFML/SFML.git
GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Configure resource files to be copied to binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)

# Copy resource files to binary directory (cross-platform)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/white_king.png
${CMAKE_CURRENT_BINARY_DIR}/bin/white_king.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/black_king.png
${CMAKE_CURRENT_BINARY_DIR}/bin/black_king.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/white_square.png
${CMAKE_CURRENT_BINARY_DIR}/bin/white_square.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/black_square.png
${CMAKE_CURRENT_BINARY_DIR}/bin/black_square.png COPYONLY)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)
add_executable(RandomKingOnChessboard ${SRC_FILES})

# Copy resource files to runtime directory after build
add_custom_command(
TARGET RandomKingOnChessboard
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources/ $<TARGET_FILE_DIR:RandomKingOnChessboard>/Resources
COMMENT "Copying required assets (textures) to runtime directory."
)

target_link_libraries(RandomKingOnChessboard PRIVATE sfml-graphics)
target_compile_features(RandomKingOnChessboard PRIVATE cxx_std_17)

# Windows-specific: Tell SFML we are linking statically
if(WIN32)
    target_compile_definitions(RandomKingOnChessboard PRIVATE SFML_STATIC)
endif()