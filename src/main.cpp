#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include <shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
	//   positions           colors            texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		3, 0, 2,
	};

	// Texture Setup
	unsigned int texture0;

	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	stbi_set_flip_vertically_on_load(true);
	int width0, height0, nrChannels0;
	unsigned char* data = stbi_load(
		(std::string(TEXTURE_DIR) + "/hashbrown.png").c_str(),
		&width0, &height0, &nrChannels0, 0
	);
    if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width0, height0, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Error: Failed to load texture 0" << std::endl;
	}
	stbi_image_free(data);
	
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	ourShader.use();
    ourShader.setInt("texture0", 0);

	// Run Window
    while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(
            glGetUniformLocation(ourShader.ID, "transform"),
            1, GL_FALSE, glm::value_ptr(trans)
        );

		// Bind Texture
        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		
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
