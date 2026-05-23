#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

const char *vertexShaderSource =
	"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vColor;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 vColor;\n"
	"void main() {\n"
	"	FragColor = vec4(vColor, 1.0);\n"
	"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "opengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error: Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, 800, 600);

	// Vertex Data
	float vertices[] = {
	//   positions           colors
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
	};

	// Vertex Buffer Object
	unsigned int VertBuffObj;
	glGenBuffers(1, &VertBuffObj);

	// Vertex Array Object
	unsigned int VertArrObj;
	glGenVertexArrays(1, &VertArrObj);

	// Element Buffer Object
	unsigned int ElementBuffObj;
	glGenBuffers(1, &ElementBuffObj);
	
	// Shader Error Setup
	int success;
	char infoLog[512];

	// Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error: Failed to compile vertex shader\n" << infoLog << std::endl;
	}

	// Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error: Failed to compile fragment shader\n" << infoLog << std::endl;
	}

	// Shader Program
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error: Failed to link shaders to shader program\n" << infoLog << std::endl;
	}

	// Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Bind Vertex Array Object
	glBindVertexArray(VertArrObj);

	// Copy Vertex Array into Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertBuffObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy Vertex Indices into Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set Vertex Attribute Pointers
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// Run Window
    while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use Shader Program when Rendering an Object
		glUseProgram(shaderProgram);

		// Bind Vertex Array
		glBindVertexArray(VertArrObj);
		// Bind Element Buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffObj);
		// Draw Triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
