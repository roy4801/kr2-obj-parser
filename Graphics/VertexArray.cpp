#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    if(m_ID)
        Delete();
}

void VertexArray::Delete()
{
    glDeleteVertexArrays(1, &m_ID);
    m_ID = 0;
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::BindVertexBuffer(const Ref<VertexBuffer> &vbo)
{
    Bind();
    vbo->Bind();

    m_VertexBuffer = vbo;
}

void VertexArray::BindIndexBuffer(const Ref<IndexBuffer> &ibo)
{
    Bind();
    ibo->Bind();
}

void VertexArray::BindVertexAttribute(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
    m_VertexBuffer->Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}
