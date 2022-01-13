#include "Renderer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include <glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "VertexBufferLayout.h"
#include "GameEngine.h"

Renderer* Renderer::sInstance{ nullptr };

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer()
{
	float windowHeight = GameEngine::GetInstance()->GameWindowHeight();
	float windowWidth = GameEngine::GetInstance()->GameWindowWidht();

	proj = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

}

void Renderer::Init()
{
	
	//shader->SetUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.0f);
}

void Renderer::Draw(Transform* transform, Texture* texture, float col, float lines, float totalColunm, float totalLines) 
{
	float h = texture->GetHeight()/(2*totalLines);
	float w = texture->GetWidth()/(2*totalColunm);
	/*float h = texture->GetHeight()/(2*lines);
	float w = texture->GetWidth()/(2*col);*/

	float sizeX = transform->myScale.X;
	float sizeY = transform->myScale.Y;

	float left = (col - 1) / totalColunm;
	float right = col / totalColunm;
	float botton = (lines - 1) / totalLines;
	float top = lines / totalLines;

	

	float positions[] = {
			-w * sizeX , -h * sizeY ,	(col-1) / totalColunm  , (lines-1)/ totalLines ,		//0
			w * sizeX , -h * sizeY,		col  / totalColunm , (lines - 1)/ totalLines,	//1
			w * sizeX , h * sizeY,		col / totalColunm, lines/ totalLines,			//2
			-w * sizeX , h* sizeY,		(col-1) / totalColunm, lines / totalLines		//3
	};

	unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0 };

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // blend pixels
	GLCall(glEnable(GL_BLEND)); // blend pixels
	//glBlendEquation(mode) -> mode (how to combine the src and dest colors Default = add

	VertexArray vertexArray;

	VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout vbLayout;
	vbLayout.Push<float>(2);
	vbLayout.Push<float>(2);
	vertexArray.AddBuffer(vertexBuffer, vbLayout);

	IndexBuffer indexBuffer{ indices, 6 };

	Shader shader{ "../Engine/basic.shader" };

	glm::vec3 translation{ transform->myPosition.X, transform->myPosition.Y , 0};
	glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
	glm::mat4 mvp = proj * view * model;

	shader.Bind();
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniformMat4f("u_MVP", mvp);

	vertexArray.Bind();
	indexBuffer.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}



void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
