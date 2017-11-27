#include <iostream>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <stdlib.h>
#include "geometry.h" 

static const struct
{
    float x, y, z;
    float r,g,b;
} vertices[3] =
{
    { -0.6f, -0.4f, 0.f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 0.f, 1.f, 0.f },
    {  0.f,   0.6f, 0.f, 0.f, 0.f, 1.f }
};

static const char* vertexShaderSrc =
"uniform mat4 MVP;\n"
"attribute vec3 position;\n"
"attribute vec3 colour;\n"
"varying vec3 outColour;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(position.x, position.y, 0.0, 1.0);\n" 
"    outColour = colour;\n"
"}\n";

static const char* fragmentShaderSrc =
"varying vec3 outColour;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(outColour, 1.0);\n"
"}\n";

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
    
    // Initialize data
    ember::Geometry triangle;
    triangle.SetupShader(vertexShaderSrc, fragmentShaderSrc);
    triangle.SetupVertices(vertices, 3, ember::Geometry::POSITION | ember::Geometry::COLOUR);
    // main render loop
    while (!glfwWindowShouldClose(win)) {
        
	// Render a triangle
	float ratio;
        int width, height;
        mat4x4 m, p, mvp;
        glfwGetFramebufferSize(win, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f,0.0f,0.5f,1.0f);	
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        triangle.SetUniform("MVP", mvp);
        triangle.Render();
	
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwDestroyWindow(win);
    return 0;
}
