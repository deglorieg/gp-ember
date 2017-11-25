#include <iostream>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <stdlib.h>
static const struct
{
    float x, y;
    float r,g,b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    { 0.6f, -0.4f, 0.f, 1.f, 0.f },
    { 0.f, 0.6f, 0.f, 0.f, 1.f }
};

static const char* vertexShaderSrc =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n" 
"    color = vCol;\n"
"}\n";

static const char* fragmentShaderSrc =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
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
    GLuint vBuffer, vShader, fragShader, program;
    glGenBuffers(1, &vBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vShader);

    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragShader);

    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    GLint mvpLoc, vposLoc, vColLoc;
    mvpLoc = glGetUniformLocation(program, "MVP");
    vposLoc = glGetAttribLocation(program, "vPos");
    vColLoc = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vposLoc);
    glVertexAttribPointer(vposLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) 0);
    glEnableVertexAttribArray(vColLoc);
    glVertexAttribPointer(vColLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) (sizeof(float) * 2));

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

        glUseProgram(program);
    	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(0);

	glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwDestroyWindow(win);
    return 0;
}
