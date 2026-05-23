#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <shader.h>

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

	// Setup shader
	Shader ourShader(
		(std::string(SHADER_DIR) + "/vertex.glsl").c_str(), 
		(std::string(SHADER_DIR) + "/fragment.glsl").c_str()
	);

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Run Window
    while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use Shader Program when Rendering an Object
		ourShader.use();

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
