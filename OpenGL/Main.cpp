//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
//
//#include <iostream>
//
//#include "Shader.h"
//#include "Camera.h"
//#include "stb_image.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//unsigned int screenWidth = 800;
//unsigned int screenHeight = 600;
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//float lastX = 400;
//float lastY = 300;
//
//float yaw = -90.0f;
//float pitch = 0.0f;
//float fov = 45.0f;
//
//bool firstMouse = true;
//
//Camera camera(cameraPos);
//
//// Metodo responsavel por alterar o tamanho do Viewport quando a janela for redimensionada
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//int main()
//{
//
//	std::cout << "Started: " << glfwGetTime() << "\n";
//
//	// Configura algumas opcoes do GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Usa o perfil Core do OpenGL
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
//
//	if (window == NULL) 
//	{
//		std::cout << "Error: Unable to initialize window" << std::endl;
//		glfwTerminate();
//		system("pause");
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// Carrega os ponteiros das funcoes do OpenGL baseado no sistema operacional
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Error: Unable to initialize GLAD" << std::endl;
//		system("pause");
//		return -1;
//	}
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	float vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0.0f,  0.0f,  0.0f),
//		glm::vec3(2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3(2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -7.5f),
//		glm::vec3(1.3f, -2.0f, -2.5f),
//		glm::vec3(1.5f,  2.0f, -2.5f),
//		glm::vec3(1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//
//	unsigned int VBO, VAO; //EBO
//	glGenBuffers(1, &VBO);
//	glGenVertexArrays(1, &VAO);
//	//glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// Primeiro parametro: Especifica qual atributo do vertice queremos configurar, isso e, o atributo 0 sao os
//	// 3 primeiros valores (que eh definido no segundo parametro) da coordenada do vertice.
//	// Segundo parametro: O tamanho do atributo do vertice, no caso do atributo 0 sao 3 valores.
//	// Terceiro parametro: O tipo dos dados.
//	// Quarto parametro: Especifica se queremos que os dados sejam normalizados.
//	// Quinto parametro: E conhecido como STRIDE e nos diz o espaco entre o proximo atributo do vertice.
//	// Sexto parametro: E o offset de onde os dados de posicao vao comecar no buffer, neste caso, no comeco do array (0).
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (void*)(6 * sizeof(float)));
//	//glEnableVertexAttribArray(2);
//
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	} else {
//		std::cout << "Failed to load texture \"" << "\"" << std::endl;
//	}
//
//	stbi_image_free(data);
//
//	unsigned int texture2;
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
//
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		std::cout << "Failed to load texture" << std::endl;
//	}
//
//	stbi_image_free(data);
//
//	Shader shader("shader.vert", "shader.frag");
//
//	shader.use();
//	shader.setInt("texture1", 0);
//	shader.setInt("texture2", 1);
//
//	glEnable(GL_DEPTH_TEST);
//
//	while (!glfwWindowShouldClose(window)) 
//	{
//
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		// Render
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		shader.use();
//
//		glm::mat4 trans;
//		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
//
//		glm::mat4 projection;
//		projection = glm::perspective(glm::radians(camera.Zoom), ((float)screenWidth / (float)screenHeight), 0.1f, 100.0f);
//
//		float radius = 10.0f;
//		glm::mat4 view;
//
//		view = camera.GetViewMatrix();
//
//		shader.setMat4("transform", trans);
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//
//		glBindVertexArray(VAO);
//
//		for (int i = 0; i < 10; i++) {
//			glm::mat4 model;
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 10.0f * i * glfwGetTime();
//			//std::cout << glfwGetTime() << "\n";
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			shader.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		// Muda o buffer de cores (um grande buffer que contem 
//		// os valores de cores para cada pixel na janela do GLFW)
//		glfwSwapBuffers(window);
//		// Verifica quais eventos foram ativados (como entradas do teclado, mouse, etc)
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//
//	system("pause");
//
//    return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow *window) 
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//
//	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	//{
//	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	//	//std::cout << "Enabled wireframe mode" << std::endl;
//	//}
//	//else if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS)
//	//{
//	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	//	//std::cout << "Disabled wireframe mode" << std::endl;
//	//}
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyBoard(Camera::MOVEMENT_FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyBoard(Camera::MOVEMENT_BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyBoard(Camera::MOVEMENT_LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyBoard(Camera::MOVEMENT_RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//		camera.ProcessKeyBoard(Camera::ROLL_LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//		camera.ProcessKeyBoard(Camera::ROLL_RIGHT, deltaTime);
//
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		camera.MovementSpeed += 1.0f;
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
//		camera.MovementSpeed = 4.0f;
//
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//
//	if (firstMouse) {
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset, true);
//
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//
//	camera.ProcessMouseScroll(yoffset);
//
//}
//
//
