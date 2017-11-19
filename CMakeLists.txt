project(EMBER)



add_executable(EMBER src/main.cpp)

# Link against GLFW3
find_package(glfw3 3.2 REQUIRED)
target_link_libraries (EMBER glfw)
