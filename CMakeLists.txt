cmake_minimum_required(VERSION 3.18)

PROJECT (Voxel-Engine)

find_package(OpenGL REQUIRED)
set (CMAKE_CXX_STANDARD 17)

file( GLOB SOURCES "src/*.cpp" "src/*.c")
link_directories(${PROJECT_SOURCE_DIR}/dependencies/libs)

add_executable( Voxel-Engine ${SOURCES} )


target_include_directories(Voxel-Engine PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/include)


target_link_libraries(Voxel-Engine PRIVATE glfw3)
target_link_libraries(Voxel-Engine PRIVATE opengl32)
