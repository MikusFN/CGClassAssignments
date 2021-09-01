#include "VertexBuffer.h"
#include "Renderer.h" 

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	//bind buffer named ao que esta na grafica
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	//tipo de dados desse array
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	//bind buffer named ao que esta na grafica
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const
{
	//Unbind buffer named ao que esta na grafica
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
