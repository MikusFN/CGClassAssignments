#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

// GLM Mathematics
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm//gtx/rotate_vector.hpp"

#include "Models/Sphere.h"
#include "Camera.h"

struct Posicao
{
	float x;
	float y;
	float z;
};

struct texCoord
{
	float u;
	float v;
};

struct normais
{
	float x;
	float y;
	float z;
};

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void ChangeShader();


// Window dimensions
const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;
int centerX = WIDTH / 2;
int centerY = HEIGHT / 2;
int isPhong = 0;
int SpotLight = 0;
int Sphere = 0;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

int main(void)
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 3 Lights", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	glfwSetCursorPos(window, centerX, centerY);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR with glew!" << std::endl;

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		const int numFacesQuad = 6;
		const int numFacesSphere = 400;
		const int cubValues = 4 * 3 * 2 * 3 * numFacesQuad;
		const int spherevalues = SphereFacesCount * SphereVertCount * SphereNormalCount * SphereTexCount;

#pragma region Quad
		float cubePositions[cubValues]
			= {
			// positions          // texture coords //normals
			//frente
		-0.5f, -0.5f, 0.5f,  0.0f,  0.0f,	0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,  1.0f,  0.0f,	0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f,  1.0f,  1.0f,	0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,  0.0f,  1.0f,	0.0f,  0.0f, 1.0f,

		//tras
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,	0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,	0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,	0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,	0.0f,  0.0f, -1.0f,

		 //esquerda
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,	-1.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,	-1.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,	-1.0f, 0.0f, 0.0f,
		 -0.5f,	0.5f, -0.5f,  0.0f,  1.0f,	-1.0f, 0.0f, 0.0f,

		 //direita
		  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,	1.0f,  0.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,	1.0f,  0.0f, 0.0f,
		  0.5f, 	0.5f,  0.5f,  0.0f,  1.0f,	1.0f,  0.0f, 0.0f,

		  //Cima
		 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,	0.0f,  1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,	0.0f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,	0.0f,  1.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f,  0.0f,  1.0f,	0.0f,  1.0f, 0.0f,

		 //Baixo
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,	0.0f,  -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,	0.0f,  -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,	0.0f,  -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,	0.0f,  -1.0f, 0.0f,
		};


#pragma endregion

		Posicao posicoesS[SphereCount] = { 0 };
		texCoord texCoodS[SphereTexCountTotal] = { 0 };
		normais normaisS[SphereCount] = { 0 };
		float sphereVertices[spherevalues] = { 0 };


		for (int i = 0, j = 0; i < SphereCount; i++, j += 3)
		{
			posicoesS[i].x = SphereVertices[j];
			posicoesS[i].y = SphereVertices[j + 1];
			posicoesS[i].z = SphereVertices[j + 2];
			normaisS[i].x = SphereNormal[j];
			normaisS[i].y = SphereNormal[j + 1];
			normaisS[i].z = SphereNormal[j + 2];
		}
		for (int i = 0, j = 0; i < SphereTexCountTotal; i++, j += 2)
		{
			texCoodS[i].u = SphereTex[j];
			texCoodS[i].v = SphereTex[j + 1];
		}
		for (int i = 0, j = 0; j < SphereFacesCount; i += 8, j += 3)
		{
			sphereVertices[i] = posicoesS[SphereFaces[j] - 1].x;
			sphereVertices[i + 1] = posicoesS[SphereFaces[j] - 1].y;
			sphereVertices[i + 2] = posicoesS[SphereFaces[j] - 1].z;
			sphereVertices[i + 3] = texCoodS[SphereFaces[j + 1] - 1].u;
			sphereVertices[i + 4] = texCoodS[SphereFaces[j + 1] - 1].v;
			sphereVertices[i + 5] = normaisS[SphereFaces[j + 2] - 1].x;
			sphereVertices[i + 6] = normaisS[SphereFaces[j + 2] - 1].y;
			sphereVertices[i + 7] = normaisS[SphereFaces[j + 2] - 1].z;
		}

		const int numIndices = 6 * numFacesQuad;
		const int numIndices1 = 6 * numFacesSphere;

		//Qualquer index buffer tem que ser um unsigned
		unsigned int indices[numIndices];
		unsigned int indices1[numIndices1];

		/*indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;*/

		for (int i = 0, j = 0; i < (numIndices); i += 6, j++)
		{

			indices[i + 0] = 0 + j + (3 * i / 6);
			indices[i + 1] = 1 + j + (3 * i / 6);
			indices[i + 2] = 2 + j + (3 * i / 6);
			indices[i + 3] = indices[i + 2];
			indices[i + 4] = 3 + j + (3 * i / 6);
			indices[i + 5] = indices[i + 0];
			/*0, 2, 3,
			0, 1, 2*/
		}

		for (int i = 0, j = 0; i < (numIndices1); i += 6, j++)
		{

			indices1[i + 0] = 0 + j + (3 * i / 6);
			indices1[i + 1] = 1 + j + (3 * i / 6);
			indices1[i + 2] = 2 + j + (3 * i / 6);
			indices1[i + 3] = indices1[i + 2];
			indices1[i + 4] = 3 + j + (3 * i / 6);
			indices1[i + 5] = indices1[i + 0];
			/*0, 2, 3,
			0, 1, 2*/
		}

		//for (size_t i = 0; i < numIndices; i++)
		//{
		//	indices[i] = i;

		//	/*0, 2, 3,
		//	0, 1, 2*/
		//}

		VertexArray va;
		VertexArray va1;
		VertexBuffer vb(cubePositions, cubValues* sizeof(float));
		VertexBuffer vb1(sphereVertices, spherevalues * sizeof(float));

		IndexBuffer ib(indices, numIndices);
		IndexBuffer ib1(indices1, numIndices1);

		VertexBufferLayout layout;
		//dois atributos 2D do quad 
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);

		va.AddBuffer(vb, layout);
		va1.AddBuffer(vb1, layout);

		// Create camera transformations
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view;
		glm::mat4 model;
		view = camera.GetViewMatrix();
		model = glm::mat4(1.0f);

		/*Shader shader2("Shaders/basic.shader");
		shader2.Bind();
		shader2.SetUniform4f("u_Color", 0.7f, 0.9f, 0.0f, 1.0f);*/

		Shader shader("Shaders/Phong.shader");
		shader.Bind();
		//shader.SetUniform4f("u_Color", 0.7f, 0.9f, 0.0f, 1.0f);

#pragma region Uniforms

		shader.SetUniform3f("viewPos", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		shader.SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));
		shader.SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));

		//Shininess
		shader.SetUniform1f("materialVert.shininess", 32.0f);
		shader.SetUniform1f("material.shininess", 32.0f);

		// Directional light
		glm::vec3 dirLight(-0.2f, -1.0f, -0.3f);
		shader.SetUniform3f("dirLightVert.direction", dirLight.x, dirLight.y, dirLight.z);
		shader.SetUniform3f("dirLightVert.ambient", 0.5f, 0.5f, 0.5f);
		shader.SetUniform3f("dirLightVert.diffuse", 0.6f, 0.6f, 0.6f);
		shader.SetUniform3f("dirLightVert.specular", 0.6f, 0.6f, 0.6f);

		shader.SetUniform3f("dirLight.direction", dirLight.x, dirLight.y, dirLight.z);
		shader.SetUniform3f("dirLight.ambient", 0.3f, 0.3f, 0.3f);
		shader.SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		shader.SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
		
		// SpotLight
		shader.SetUniform3f("spotLightVert.position", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		shader.SetUniform3f("spotLightVert.direction", camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		shader.SetUniform3f("spotLightVert.ambient", 0.0f, 0.0f, 0.0f);
		shader.SetUniform3f("spotLightVert.diffuse", 1.0f, 1.0f, 1.0f);
		shader.SetUniform3f("spotLightVert.specular", 1.0f, 1.0f, 1.0f);
		shader.SetUniform1f("spotLightVert.constant", 1.0f);
		shader.SetUniform1f("spotLightVert.linear", 0.09f);
		shader.SetUniform1f("spotLightVert.quadratic", 0.032f);
		shader.SetUniform1f("spotLightVert.cutOff", glm::cos(glm::radians(12.5f)));
		shader.SetUniform1f("spotLightVert.outerCutOff", glm::cos(glm::radians(15.0f)));

		shader.SetUniform3f("spotLight.position", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		shader.SetUniform3f("spotLight.direction", camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		shader.SetUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		shader.SetUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		shader.SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
		shader.SetUniform1f("spotLight.constant", 1.0f);
		shader.SetUniform1f("spotLight.linear", 0.09f);
		shader.SetUniform1f("spotLight.quadratic", 0.032f);
		shader.SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		shader.SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		shader.SetUniform1i("VertCalc", isPhong);
		shader.SetUniform1i("SpotLightOn", SpotLight);
		shader.SetUniform1i("SpotLightOnVert", SpotLight);

		Texture texture("res/textures/container2.png");
		Texture texture1("res/textures/container2.png");
		Texture texture2("res/textures/container2_specular.png");
		Texture texture3("res/textures/container2_specular.png");
		texture.Bind(0);
		texture1.Bind(1);
		texture2.Bind(2);
		texture3.Bind(3);
		shader.SetUniform1i("materialVert.diffuse", 0);
		shader.SetUniform1i("material.diffuse", 1);
		shader.SetUniform1i("materialVert.specular", 2);
		shader.SetUniform1i("material.specular", 3);

#pragma endregion

		Renderer renderer;

		//float r = 0.0f;
		//float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			// Calculate deltatime of current frame
			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
			DoMovement();


			renderer.Clear();

			shader.Bind();
			//shader.SetUniform4f("u_Color", r, 0.9f, 0.0f, 1.0f);

			shader.SetUniform3f("viewPosVert", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
			shader.SetUniform3f("viewPos", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

			view = camera.GetViewMatrix();

			shader.SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));
			shader.SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

			//model = glm::translate(model, glm::vec3(1.0f));
			if (keys[GLFW_KEY_X])
			{
				model = glm::rotate(model, 0.05f, glm::vec3(0.0f, 0.1f, 0.0f));
			}
			if (keys[GLFW_KEY_Z])
			{
				model = glm::rotate(model, -0.05f, glm::vec3(0.0f, 0.1f, 0.0f));
			}
			shader.SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));

			dirLight = glm::rotateX(dirLight, 0.005f);
			dirLight = glm::rotateY(dirLight, 0.005f);
			dirLight = glm::rotateZ(dirLight, 0.005f);

			shader.SetUniform3f("dirLightVert.direction", dirLight.x, dirLight.y, dirLight.z);
			shader.SetUniform3f("spotLightVert.position", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
			shader.SetUniform3f("spotLightVert.direction", camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);

			shader.SetUniform3f("dirLight.direction", dirLight.x, dirLight.y, dirLight.z);
			shader.SetUniform3f("spotLight.position", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
			shader.SetUniform3f("spotLight.direction", camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);


			texture.Bind(0);
			texture1.Bind(1);
			texture2.Bind(2);
			texture3.Bind(3);
			shader.SetUniform1i("materialVert.diffuse", 0);
			shader.SetUniform1i("material.diffuse", 1);
			shader.SetUniform1i("materialVert.specular", 2);
			shader.SetUniform1i("material.specular", 3);

			ChangeShader();
			
			shader.SetUniform1i("VertCalc", isPhong);
			shader.SetUniform1i("SpotLightOn", SpotLight);
			shader.SetUniform1i("SpotLightOnVert", SpotLight);

			if (Sphere==0)
			{
				renderer.Draw(va1, ib1, shader);
			}
			else
			{
				renderer.Draw(va, ib, shader);
			}

			/*if (isPhong)
			{
				shader2.UnBind();
				shader.Bind();
				renderer.Draw(va, ib, shader);
			}
			else
			{
				shader.UnBind();
				shader2.Bind();*/
				//renderer.Draw(va, ib, shader2);
			//}
			/*if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment += 0.05f;

			r += increment;*/

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void ChangeShader()
{
	if (keys[GLFW_KEY_C])
	{
		isPhong = !isPhong;
	}
	if (keys[GLFW_KEY_O])
	{
		SpotLight = !SpotLight;
	}
	if (keys[GLFW_KEY_M])
	{
		Sphere = !Sphere;
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	/*if (xPos<0||xPos>WIDTH||yPos<0||yPos>HEIGHT)
		glfwSetCursorPos(window, centerX, centerY);*/
	if (xPos != centerX || yPos != centerY)
	{
		if (firstMouse)
		{
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}

		GLfloat xOffset = xPos - lastX;
		GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

		lastX = xPos;
		lastY = yPos;

		/*if (xPos != centerX || yPos != centerY)
		glfwSetCursorPos(window, centerX, centerY);*/

		camera.ProcessMouseMovement(xOffset, yOffset);
	}


}
