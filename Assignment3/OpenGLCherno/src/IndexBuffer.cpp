#include "IndexBuffer.h"
#include "Renderer.h" 

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
	:m_Count(count)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	//bind buffer named ao que esta na grafica
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	//tipo de dados desse array
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	//bind buffer named ao que esta na grafica
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
	//Unbind buffer named ao que esta na grafica
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
