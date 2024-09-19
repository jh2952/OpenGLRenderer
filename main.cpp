#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "VertexArray.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

using VertexArrayID  = unsigned int;
using TextureID = unsigned int;
using VertexIndex = unsigned int;

struct VertexData
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float s;
	float t;
};

std::vector<VertexData> vertices = 
{
	// Position                // Colours         // UV Coords
	{ -0.50f,  0.50f,  0.00f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f },
	{  0.50f,  0.50f,  0.00f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f },
	{ -0.50f, -0.50f,  0.00f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f },
	{  0.50f, -0.50f,  0.00f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f },
};

std::vector<VertexIndex> indices =
{
	0, 1, 2,
	1, 3, 2
};

int main()
{	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		assert(false && "Failed to create GLFW window.");
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		assert(false && "Failed to initialize GLAD");
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	VertexBuffer vb(vertices.data(), vertices.size() * sizeof(VertexData));
	ElementBuffer eb(indices.data(), indices.size() * sizeof(VertexIndex));

	VertexArray VAO(vb, eb);
	VAO.AddVertexAttribute(3, GL_FLOAT, sizeof(VertexData), 0);
	VAO.AddVertexAttribute(3, GL_FLOAT, sizeof(VertexData), 3 * sizeof(float));
	VAO.AddVertexAttribute(2, GL_FLOAT, sizeof(VertexData), 6 * sizeof(float));
	
	Texture2D texture1("Data\\container.jpg", GL_RGB);
	Texture2D texture2("Data\\awesomeface.png", GL_RGBA);

	Shader shaderProgram("vertex.vs", "fragment.fs");

	shaderProgram.Use();
	shaderProgram.SetInt("texture1", 0);
	shaderProgram.SetInt("texture2", 1);

	texture2.SetFilterMode(GL_NEAREST, GL_NEAREST);

	glm::mat4 trans1 = glm::mat4(1.0f);
	trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0.0f));

	glm::mat4 trans2 = glm::mat4(1.0f);
	trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));


	while (!glfwWindowShouldClose(window))
	{
		static float time = 0;

		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Use();
		texture1.Activate(GL_TEXTURE0);
		texture2.Activate(GL_TEXTURE1);
		VAO.Bind();

		shaderProgram.SetMatrix4x4f("transform", trans1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		trans2 = glm::mat4(1.0f); // reset it to identity matrix
		trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = static_cast<float>(sin(glfwGetTime()));
		trans2 = glm::scale(trans2, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		shaderProgram.SetMatrix4x4f("transform", trans2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
