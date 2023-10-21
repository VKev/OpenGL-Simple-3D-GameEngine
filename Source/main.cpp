#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"../Header/shaderClass.h"
#include"../Header/VAO.h"
#include"../Header/VBO.h"
#include"../Header/EBO.h"
#include"../Header/Texture.h"
#include"../Header/Camera.h"



// Vertices coordinates
GLfloat pyramid_vert[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint pyramid_indx[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightsrc_vert[] =
{ //     COORDINATES     //
	-0.1f+1.0f, -0.1f + 1.0f,  0.1f + 1.0f,
	-0.1f + 1.0f, -0.1f + 1.0f, -0.1f + 1.0f,
	 0.1f + 1.0f, -0.1f + 1.0f, -0.1f + 1.0f,
	 0.1f + 1.0f, -0.1f + 1.0f,  0.1f + 1.0f,
	-0.1f + 1.0f,  0.1f + 1.0f,  0.1f + 1.0f,
	-0.1f + 1.0f,  0.1f + 1.0f, -0.1f + 1.0f,
	 0.1f + 1.0f,  0.1f + 1.0f, -0.1f + 1.0f,
	 0.1f + 1.0f,  0.1f + 1.0f,  0.1f + 1.0f
};

GLuint lightsrc_indx[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_Game", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);


	
	//Generate buffer
	VAO pyramidVAO;
	pyramidVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO pyramidVBO(pyramid_vert, sizeof(pyramid_vert));
	// Generates Element Buffer Object and links it to indices
	EBO pyramidEBO(pyramid_indx, sizeof(pyramid_indx));
	// Links VBO to VAO
	GLsizeiptr pyramidAtrSize = 11 * sizeof(float);
	pyramidVAO.LinkAttrib(pyramidVBO, 0, 3, GL_FLOAT, pyramidAtrSize, (void*)0);
	pyramidVAO.LinkAttrib(pyramidVBO, 1, 3, GL_FLOAT, pyramidAtrSize, (void*)(3 * sizeof(float)));
	pyramidVAO.LinkAttrib(pyramidVBO, 2, 2, GL_FLOAT, pyramidAtrSize, (void*)(6 * sizeof(float)));
	pyramidVAO.LinkAttrib(pyramidVBO, 3, 3, GL_FLOAT, pyramidAtrSize, (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	pyramidVAO.Unbind();
	pyramidVBO.Unbind();
	pyramidEBO.Unbind();


	VAO lightsrcVAO;
	lightsrcVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightsrcVBO(lightsrc_vert, sizeof(lightsrc_vert));
	// Generates Element Buffer Object and links it to indices
	EBO lightsrcEBO(lightsrc_indx, sizeof(lightsrc_indx));
	// Links VBO to VAO
	GLsizeiptr lightsrcAtrSize = 3 * sizeof(float);
	lightsrcVAO.LinkAttrib(lightsrcVBO, 0, 3, GL_FLOAT, lightsrcAtrSize, (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightsrcVAO.Unbind();
	lightsrcVBO.Unbind();
	lightsrcEBO.Unbind();

	//variable
	glm::vec4 lightColor = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	//Shader program var
	Shader defaultShader("default.vert", "default.frag","Shader/");
	
	Texture wallTex( ("Texture/wall.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	wallTex.texUnit(defaultShader, "tex0", 0);

	defaultShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(defaultShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	


	Shader lightShader("light.vert", "light.frag", "Shader/");

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	//update var
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	


	glEnable(GL_DEPTH_TEST);
	// Update()
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.speed = 0.0005f;
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		
		defaultShader.Activate();
		camera.Matrix(defaultShader, "camMatrix");

		wallTex.Bind();
		pyramidVAO.Bind(); 
		glUniform3f(glGetUniformLocation(defaultShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		
		
		glDrawElements(GL_TRIANGLES, sizeof(pyramid_indx)/sizeof(int), GL_UNSIGNED_INT, 0);


		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightsrcVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightsrc_indx)/sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}



	// Delete all the objects have created
	pyramidVAO.Delete();
	pyramidVBO.Delete();
	pyramidEBO.Delete();
	wallTex.Delete();
	defaultShader.Delete();

	lightsrcVAO.Delete();
	lightsrcVBO.Delete();
	lightsrcEBO.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}