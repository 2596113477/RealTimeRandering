#define GLEW_STATIC
#include <GL/glew.h>//链接opengl
#include<GLFW/glfw3.h>//窗口化
#include<iostream>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include"Shader.h"
#include"Loadimg.h"
#include"Camera.h"

#pragma region Config
//Screen
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//input
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 1.0f;
bool isFirstMouse = true;

//time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

#pragma endregion


#pragma region ModelData
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
#pragma endregion
#pragma region Camera Declare
//init Camera
Camera* camera = new Camera(glm::vec3(0, 0, 10.0f));
//float lastX;
//float lastY;
//bool isFirstMouse = true;
#pragma endregion

#pragma region Input Declare
//绑定esc退出,控制按键
void processInput (GLFWwindow* window) {
	if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->ProcessKeyboard(FORWARD,deltaTime);
	}

	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->ProcessKeyboard(LEFT, deltaTime);
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->ProcessKeyboard(RIGHT, deltaTime);
	}

	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera->ProcessKeyboard(LIFT, deltaTime);
	}

	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera->ProcessKeyboard(DOWN, deltaTime);
	}

}

	void mouse_callback(GLFWwindow * window, double xPosIn, double yPosIn) {
		float xPos = static_cast<float>(xPosIn);
		float yPos = static_cast<float>(yPosIn);
			
		if (isFirstMouse) {
			lastX = xPos;
			lastY = yPos;
			isFirstMouse = false;
		}

		float xOffset = lastX - xPos;
		float yOffset = yPos - lastY;

		
		lastX = xPos;
		lastY = yPos;

		camera->ProcessMouseMovement(xOffset, yOffset);
	}
	void sroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
		camera->ProcessMouseScroll(static_cast<float>(yOffset));
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

#pragma endregion

int main() {
	#pragma region Open Window
	//init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//版本号3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MY OpenGL", NULL, NULL);

	if (window == NULL) {
		printf("failed");
		glfwTerminate();
		return -1;
	}//Open GLFW window，创建失败则返回-1.

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, sroll_callback);

	glewExperimental = true;//实验性模式
	if (glewInit() != GLEW_OK) {
		printf("init glew failed");
		glfwTerminate();
		return -1;
	}//init GLEW
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);//视口
	glEnable(GL_DEPTH_TEST);//开启深度测试
	//glEnable(GL_CULL_FACE);背面剔除
	//glCullFace(GL_BACK);
#pragma endregion

	#pragma region VBO VAO EBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//绑定VAO
	glBindVertexArray(VAO);
    //复制顶点数组到缓冲中供OpenGL使用
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//顶点索引

	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);   
	glLinkProgram(shaderProgram);*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//设置顶点属性指针
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//设置顶点属性指针
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//设置顶点属性指针
	glEnableVertexAttribArray(2);
#pragma endregion

	#pragma region Material
	Shader* myshader = new Shader("vertexSource.vert", "fragmentSource.frag");

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(myshader->ID, "ourColor");

	//load img
	Loadimg* awesome = new Loadimg("awesomeface.png");

#pragma endregion

	#pragma region Prepare MVP
	//模型变换
	glm::mat4 modelMat;
	modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(1.0f, 0, 0));
	modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(0, 1.0f, 0));
	//视图变换
	glm::mat4 viewMat;
	/*viewMat = camera->GetViewMatrix();*/
	//透视变换
	glm::mat4 projMat;
	

	float x = 0;
#pragma endregion

	#pragma region RenderLoop
	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//输入
		processInput(window);
		
		//清空颜色缓冲
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态使用函数（color、depth、stencil）

		viewMat = camera->GetViewMatrix();

		/*timeValue = glfwGetTime();
		greenValue = (sin(timeValue) / 2) + 0.5;*/
		x +=0.1f;
		glBindVertexArray(VAO);
		//渲染指令
		for (int i = 0; i < 10; i++) {
			myshader->Use();
			glm::mat4 Mat;

			Mat = glm::translate(Mat, cubePositions[i]);
			Mat = glm::rotate(Mat, glm::radians(x), glm::vec3(0, 1.0f, 0));
			projMat = glm::perspective(glm::radians(camera->zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);


			//MVP
			myshader->SetUniformMatrix4fv("modelMat", Mat);
			myshader->SetUniformMatrix4fv("viewMat", viewMat);
			myshader->SetUniformMatrix4fv("projMat", projMat);
			myshader->SetUniform3fv("objColor", glm::vec3(0.5f,0.2f,0.7f));

			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(Mat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			/*glUniform1i(glGetUniformLocation(myshader->ID, "ourTexture"), 0);*/
			glUniform3f(glGetUniformLocation(myshader->ID, "objColor"),0.5f, 0.2f, 0.7f);
			glDrawArrays(GL_TRIANGLES, 0, 36);


		}

		/*glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

		//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

	#pragma region Exit Program
	glfwTerminate();
	return 0;
#pragma endregion
}