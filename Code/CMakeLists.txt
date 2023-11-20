cmake_minimum_required(VERSION 3.16)
project(Pong LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Pong
#headers
    headers/Processes.hpp
    headers/Controller.hpp
    headers/Paddle.hpp
    headers/Ball.hpp
    #utils
        headers/utils/All.hpp
        headers/utils/Basic.hpp
        headers/utils/StringUtils.hpp
        headers/utils/Vectors.hpp

#src
    src/Main.cpp
    src/Processes.cpp
    src/Paddle.cpp
    src/Ball.cpp
        #utils
        src/utils/StringUtils.cpp
)
target_include_directories(Pong PRIVATE headers)
target_link_libraries(Pong PRIVATE sfml-graphics)
target_compile_features(Pong PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Pong
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Pong>
        VERBATIM)
endif()

install(TARGETS Pong)
