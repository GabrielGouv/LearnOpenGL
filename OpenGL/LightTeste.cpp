#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int screenWidth = 800;
unsigned int screenHeight = 600;

glm::vec3 cameraPos = glm::vec3(-1.8f, 3.4f, -0.12f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(2.5f, -1.0f, 4.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 400;
float lastY = 300;

float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;

bool firstMouse = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Camera camera(cameraPos);

// Metodo responsavel por alterar o tamanho do Viewport quando a janela for redimensionada
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{

	std::cout << "Started: " << glfwGetTime() << "\n";

	// Configura algumas opcoes do GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Usa o perfil Core do OpenGL

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Error: Unable to initialize window" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Carrega os ponteiros das funcoes do OpenGL baseado no sistema operacional
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Unable to initialize GLAD" << std::endl;
		system("pause");
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float vertices_plano[] = {
		-0.5f, 0.0f, -0.5f,  0.0f, 1.0f,  0.0f,
		0.5f, 0.0f, -0.5f,  0.0f, 1.0f,  0.0f,
		0.5f, 0.0f,  0.5f,  0.0f, 1.0f,  0.0f,
		0.5f, 0.0f,  0.5f,  0.0f, 1.0f,  0.0f,
		-0.5f, 0.0f,  0.5f,  0.0f, 1.0f,  0.0f,
		-0.5f, 0.0f, -0.5f,  0.0f, 1.0f,  0.0f,
	};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, cubeVAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int planoVBO, planoVAO;
	glGenBuffers(1, &planoVBO);
	glGenVertexArrays(1, &planoVAO);

	glBindBuffer(GL_ARRAY_BUFFER, planoVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_plano), vertices_plano, GL_STATIC_DRAW);

	glBindVertexArray(planoVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader lightShader("light.vert", "light.frag");
	Shader lampShader("lamp.vert", "lamp.frag");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightPos = glm::vec3(cos(glfwGetTime()) + 3.0f, 1.0f, 2.0f);

		lightShader.use();
		lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), ((float)screenWidth / (float)screenHeight), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		lightShader.setVec3("lightPos", lightPos);
		lightShader.setVec3("viewPos", camera.Position);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(2.5f, -1.0f, 4.0f));
		lightShader.setMat4("model", model);

		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lampShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		lightShader.use();
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.5f, -1.5f, 4.0f));
		model = glm::scale(model, glm::vec3(10.0f));
		//lightShader.setVec3("lightPos", lightPos);
		lightShader.setMat4("model", model);

		glBindVertexArray(planoVAO); 
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	system("pause");

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	//std::cout << "Enabled wireframe mode" << std::endl;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS)
	//{
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//	//std::cout << "Disabled wireframe mode" << std::endl;
	//}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::MOVEMENT_FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::MOVEMENT_BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::MOVEMENT_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::MOVEMENT_RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::ROLL_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::ROLL_RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::MOVEMENT_UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.ProcessKeyBoard(Camera::MOVEMENT_DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.MovementSpeed += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
		camera.MovementSpeed = 4.0f;

	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_EQUAL) != GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	camera.ProcessMouseScroll(yoffset);

}


