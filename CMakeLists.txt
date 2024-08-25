cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/white_king.png
    ${CMAKE_CURRENT_BINARY_DIR}/Debug COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/white_king.png
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/black_king.png
    ${CMAKE_CURRENT_BINARY_DIR}/Debug COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/black_king.png
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/white_square.png
    ${CMAKE_CURRENT_BINARY_DIR}/Debug COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/white_square.png
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/black_square.png
    ${CMAKE_CURRENT_BINARY_DIR}/Debug COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/black_square.png
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)
add_executable(main ${SRC_FILES} Resources/white_king.png Resources/black_king.png Resources/white_square.png Resources/black_square.png)

target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
