#pragma once

#include <GL/glew.h>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


//funccao assert que para a execucao ( like a breakpoint) e é especifica pra o MSVC do visual studio
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__,__LINE__ )) // #x -> transforma o x numa string e o file e line sao as macros que definem este dois parametros no sistema
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:	
	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

private:

};
