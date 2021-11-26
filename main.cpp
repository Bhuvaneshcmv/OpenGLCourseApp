#include <stdio.h>
#include <string.h>
#include <cmath>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.141592f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

bool dir = true;

float trioffset = 0.0f;
float trimaxOffset = 0.7f;
float triIncrement = 0.0005f;

float curAngle;
float maxAngle = 360;
float deltaAngle = 0.1f;

float scaleDelta = 0.01f;
float maxScale = 0.8f;
float curScale = 0.4f;
float minScale = 0.0f;

// Vertex Shader code
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f,-1.0f,1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices,indices,12,12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices,indices,12,12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateObjects();
	CreateShaders();

	glm::mat4 projection = glm::perspective((float)45,((GLfloat)bufferWidth/(GLfloat)bufferHeight),0.1f,100.0f);
	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (dir)
		{
			trioffset += triIncrement;
		}

		else
		{
			trioffset -= triIncrement;
		}

		if (abs(trioffset) >= trimaxOffset)
		{
			dir = !dir;
		}

		curAngle += deltaAngle;
		if (curAngle >= maxAngle)
		{
			curAngle -= maxAngle;
		}

		curScale += scaleDelta;
		if (curScale >= maxScale || curScale <= minScale)
		{
			scaleDelta = -scaleDelta;
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();

		GLuint uniformProjection = 0, uniformModel = 0;
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		glm::mat4 model(1.0f);

		

		model = glm::translate(model, glm::vec3(trioffset, 0, -2.5));		
		model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-trioffset, 1, -2.5));
		model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}