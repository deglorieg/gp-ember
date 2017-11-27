cmake_minimum_required(VERSION 3.0)
project(EMBER)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/include/")

add_executable(EMBER src/main.cpp src/geometry.h src/geometry.cpp)

# Link against GLFW3
find_package(glfw3 3.2 REQUIRED)
find_package(epoxy REQUIRED)
find_package(OpenGL REQUIRED)

if(OPENGL_FOUND AND epoxy_FOUND)
 target_include_directories(EMBER PUBLIC ${OPENGL_INCLUDE_DIR} ${epoxy_INCLUDE_DIR})
 target_link_libraries(EMBER glfw ${epoxy_LIBRARY} ${OPENGL_gl_LIBRARY})

endif()

#target_link_libraries (EMBER glfw)
