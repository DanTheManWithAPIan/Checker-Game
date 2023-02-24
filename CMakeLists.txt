cmake_minimum_required(VERSION 3.24)
project(C__FUN)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(../SDL2-devel-2.26.3-mingw/SDL2-2.26.3/x86_64-w64-mingw32/include)
link_directories(../SDL2-devel-2.26.3-mingw/SDL2-2.26.3/x86_64-w64-mingw32/lib)

add_executable(C__FUN main.cpp)

target_link_libraries(C__FUN mingw32 SDL2main SDL2 ${OPENGL_LIBRARIES})