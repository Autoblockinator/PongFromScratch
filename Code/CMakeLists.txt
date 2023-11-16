cmake_minimum_required(VERSION 3.16)
project(Pong LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(Pong ${SOURCE_FILES})
target_include_directories(Pong PRIVATE hdr)
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