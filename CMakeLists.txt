cmake_minimum_required(VERSION 3.18)

PROJECT (minecraft)

find_package(OpenGL REQUIRED)
set (CMAKE_CXX_STANDARD 17)

file( GLOB SOURCES "src/*.cpp" "src/*.c")
link_directories(${PROJECT_SOURCE_DIR}/dependencies/libs)

add_executable( minecraft ${SOURCES} )


target_include_directories(minecraft PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/include)


target_link_libraries(minecraft PRIVATE glfw3)
target_link_libraries(minecraft PRIVATE opengl32)
