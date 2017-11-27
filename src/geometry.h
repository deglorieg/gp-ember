#include <stdint.h>
#include <linmath.h>

namespace ember
{
    class Geometry
    {
    public:
        Geometry();
    
        void SetupShader(const char* vertexShader, const char* fragmentShader);
        void SetupVertices(const void* data, uint32_t numVerts, uint32_t attribFlags);
        typedef struct {
            float x,y;
            float u,v;
        } VertexDecl;

        enum eVertexAttributes
        {
            POSITION    = 1 << 0,
            COLOUR      = 1 << 1,
            UV          = 1 << 2
        };

        void SetUniform(const char* unifName, mat4x4 matrix); 

        void Render();
    private:
        uint32_t m_uiProgram;
        uint32_t m_uiVertexHandle, m_uiFragmentHandle;
        uint32_t m_uiVBHandle;
        uint32_t m_uiNumVertices;
        uint32_t m_uiVertexStride;
    };
};
