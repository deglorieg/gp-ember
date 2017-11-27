#include "geometry.h"
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <iostream>
#define CHECK_FLAGS(mask, flag) (mask & flag) != 0

// Constructor
ember::Geometry::Geometry()
{
}

void ember::Geometry::SetupShader(const char* vertexShader, const char* fragmentShader)
{
    m_uiVertexHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_uiVertexHandle, 1, &vertexShader, NULL);
    glCompileShader(m_uiVertexHandle);

    m_uiFragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_uiFragmentHandle, 1, &fragmentShader, NULL);
    glCompileShader(m_uiFragmentHandle);

    m_uiProgram = glCreateProgram();
    glAttachShader(m_uiProgram, m_uiVertexHandle);
    glAttachShader(m_uiProgram, m_uiFragmentHandle);
    glLinkProgram(m_uiProgram);
}

uint32_t count_1bits(uint32_t x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

void ember::Geometry::SetupVertices(const void* data, uint32_t numVerts, uint32_t attribFlags)
{
    const uint32_t numAttributes = count_1bits(attribFlags);
    uint32_t m_uiVertexStride = 0;
    m_uiVertexStride += CHECK_FLAGS(attribFlags, POSITION) ? 3 * sizeof(float) : 0;
    m_uiVertexStride += CHECK_FLAGS(attribFlags, COLOUR) ? 3 * sizeof(float) : 0;
    m_uiVertexStride += CHECK_FLAGS(attribFlags, UV) ? 2 * sizeof(float) : 0;
    
    // Initialize data
    glGenBuffers(1, &m_uiVBHandle);
    m_uiNumVertices = numVerts;
    glBindBuffer(GL_ARRAY_BUFFER, m_uiVBHandle);
    glBufferData(GL_ARRAY_BUFFER, numVerts * m_uiVertexStride, data, GL_STATIC_DRAW);
 
    size_t offset = 0;
    if(CHECK_FLAGS(attribFlags, POSITION))
    {
        GLuint vPosLoc = glGetAttribLocation(m_uiProgram, "position");
        glEnableVertexAttribArray(vPosLoc);
        glVertexAttribPointer(vPosLoc, 3, GL_FLOAT, GL_FALSE, m_uiVertexStride, (void *) 0);
        offset += (sizeof(float) * 3);
    }
    if(CHECK_FLAGS(attribFlags, COLOUR))
    {
        GLuint vColLoc = glGetAttribLocation(m_uiProgram, "colour");
        glEnableVertexAttribArray(vColLoc);
        glVertexAttribPointer(vColLoc, 3, GL_FLOAT, GL_FALSE, m_uiVertexStride, (void *) offset);
        offset += (sizeof(float) * 3);
    }
    if(CHECK_FLAGS(attribFlags, UV))
    {
        GLuint vUVLoc = glGetAttribLocation(m_uiProgram, "uv");
        glEnableVertexAttribArray(vUVLoc);
        glVertexAttribPointer(vUVLoc, 2, GL_FLOAT, GL_FALSE, m_uiVertexStride, (void *) offset);
        offset += (sizeof(float) * 2);
    }
}

void ember::Geometry::SetUniform(const char* unifName, mat4x4 matrix)
{
    uint32_t uniformLoc = glGetUniformLocation(m_uiProgram, unifName);
    glUseProgram(m_uiProgram);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, (const GLfloat*) matrix);
}

void ember::Geometry::Render()
{ 
    glBindBuffer(GL_ARRAY_BUFFER, m_uiVBHandle);
    glDrawArrays(GL_TRIANGLES, 0, m_uiNumVertices);
}


#undef CHECK_FLAGS
