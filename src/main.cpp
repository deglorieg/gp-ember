#include <iostream>
#include <GLFW/glfw3.h>
#include <stdlib.h>
int main()
{
    if (!glfwInit()) {
        std::cerr << "Can't initialize GLFW" << std::endl;
        exit (EXIT_FAILURE);
    } else {
        std::cout << "Success" << std::endl;
    }


    std::cout << "Hello World!" << std::endl;
    return 0;
}
