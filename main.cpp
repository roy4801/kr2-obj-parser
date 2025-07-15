#include <iostream>

#include "parser.h"
#include "Log.h"
#include <glad/glad.h>

#include <Core/OpenGLApplication.h>
#include <Core/Ref.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Graphics/VertexArray.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>

GLfloat vertices[] =
{
    // COORDINATES       /     COLORS          /   TexCoord
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // 0 Lower left corner
    -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // 1 Upper left corner
    0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // 2 Upper right corner
    0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // 3 Lower right corner
};

GLuint indices[] = {
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
};


class MyApp : public OpenGLApplication
{
public:
    Ref<Shader> shader;
    Ref<Texture> texture;
    Ref<VertexArray> vao;
    Ref<VertexBuffer> vbo;
    Ref<IndexBuffer> ibo;

    MyApp(int argc, char* argv[])
        : OpenGLApplication(argc, argv)
    {
        // !!! OpenGL context is INVALID here !!!
    }
    ~MyApp() = default;

    bool Init() override
    {
        // Create Shaderf
        shader = MakeRef<Shader>();
        shader->Load("assets/default.vert", "assets/default.frag");
        // Create Texture
        texture = MakeRef<Texture>("assets/missing.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        texture->TexUnit(shader, "tex0", 0);
        // Create VAO, VBO, and EBO
        vao = MakeRef<VertexArray>();
        vbo = MakeRef<VertexBuffer>();
        ibo = MakeRef<IndexBuffer>();
        // Bind vbo and send vbo to GPU
        vao->BindVertexBuffer(vbo);
        vbo->Store(vertices, sizeof(vertices));
        // Bind ibo and send ibo to GPU
        vao->BindIndexBuffer(ibo);
        ibo->Store(indices, sizeof(indices));
        // Setting Vertex Attribute Array
        vao->BindVertexAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
        vao->BindVertexAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        vao->BindVertexAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        vao->Unbind();
        IndexBuffer::Clear();
        VertexBuffer::Clear();

        return true;
    }

    void Shutdown() override
    {
    }

    void ProcessInput() override
    {
//        LOG_INFO("ProcessInput");
    }

    void Update(float dt) override
    {
//        LOG_INFO("Update {}", dt);
    }

    void Render() override
    {
        texture->Bind();
        vao->Bind();
        // Draw primitives, number of indices, type, index of indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

int main(int argc, char* argv[])
{
    // Test OBJ parser first
    std::cout << "Testing OBJ parser with bunny.obj..." << std::endl;
    ObjParser parser("../bunny.obj");
    
    if (!parser.isEmpty()) {
        parser.PrintStatistics();
    } else {
        std::cout << "Failed to parse OBJ file or file is empty." << std::endl;
    }
    
    // Try to run the OpenGL application
    MyApp app(argc, argv);
    app.Run();
    return 0;
}
