project(EMBER)



add_executable(EMBER src/main.cpp)

# Link against GLFW3
find_package(glfw3 3.2 REQUIRED)

find_package(OpenGL REQUIRED)

if(OPENGL_FOUND)
 target_include_directories(EMBER PUBLIC ${OPENGL_INCLUDE_DIR})
 target_link_libraries(EMBER glfw  ${OPENGL_gl_LIBRARY})

endif()

#target_link_libraries (EMBER glfw)
