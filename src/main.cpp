#include <iostream>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <stdlib.h>

void errorCallback(int i, const char* msg)
{
     std::cout << i << msg << std::endl;
}

int main()
{
    if (!glfwInit()) {
        std::cerr << "Can't initialize GLFW" << std::endl;
        exit (EXIT_FAILURE);
    } else {
        std::cout << "Success" << std::endl;
    }
    glfwSetErrorCallback(errorCallback);

    GLFWwindow *win;
    win = glfwCreateWindow (800, 600, "EMBER", NULL, NULL);
    
    if(!win)
	exit(EXIT_FAILURE);

    glfwMakeContextCurrent(win);
    while (!glfwWindowShouldClose(win)) {
        glfwSwapBuffers(win);
        glfwPollEvents();
	//glfwWaitEvents();
	glClearColor(1.0f,0.0f,0.5f,1.0f);
	
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
