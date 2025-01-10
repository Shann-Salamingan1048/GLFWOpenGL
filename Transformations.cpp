#include "Transformations.h"
void Transformations::initGLFW()
{
	// init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
	// set the window hint to get forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// set the window hint to disable resizing
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}
void Transformations::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// if the user resizes the window, the viewport should be adjusted as well
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void Transformations::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void Transformations::processInput(GLFWwindow* window, float &x, float &y)
{
	const float max = 1.0f;
	const float addMove = 0.1f;
	// if the user presses the space key, the window should close
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if(x != max)
			x += addMove;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if(x != -max)
			x -= addMove;
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (y != max)
			y += addMove;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (y != -max)
			y -= addMove;
	}
}
void Transformations::Exercise5_2ex2()
{
	initGLFW();
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "Open Glfw and Glad", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}
	// Make the context of our window the current active context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Synchronizes the Frame Rate with the Monitor's Refresh Rate:
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		return;
	}
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Shader 
	Shader shaderProgram("GLSL/exercise5_1.vert", "GLSL/exercise5_1.frag");

	GLfloat vertices[] =
	{
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	// change the texture coords, nth.0f is the nth times the texture will be repeated
	// this is because of the gl_repeat
	GLuint indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	// create EBO and bind and send data
	EBO ebo1(indices, sizeof(indices));

	// size 5 thats why it is 5
	// Position attribute
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
	// Color attribute
	// will start at 3rd index thats why it is 3
	vao1.LinkAttrib(vbo1, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();
	// Texture
	// 1st texture
	GLuint texture1 = 0;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	// S => x-axis, T => y-axis, R => z-axis
	// somce it is 2D texture we are using S and T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	// Flip the image vertically before loading
	stbi_set_flip_vertically_on_load(true);
	GLint width = 0, height = 0, nrChannels = 0;
	unsigned char* data = stbi_load("Resources/Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);


	// 2nd texture
	GLuint texture2 = 0;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the texture
	data = stbi_load("Resources/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);

	// Activate the shader
	shaderProgram.Activate();
	// Tell the shader that the texture is in texture unit 0
	shaderProgram.setInt("texture1", 0); // same name as in the fragment shader like texture1 uniforms
	// Tell the shader that the texture is in texture unit 1
	shaderProgram.setInt("texture2", 1); // same name as in the fragment shader like texture1 uniforms

	// Render loop
	// move
	//float x = 0.0f, y = 0.0f;
	while (!glfwWindowShouldClose(window))
	{

		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// create transformations

		//first container
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix 
		// to identity matrix first
		transform = glm::rotate(transform, static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate the object. x, y, z
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); // x , y, z, move the object

		// activate the shader
		// get matrix's uniform location and set matrix
		shaderProgram.Activate();
		GLuint transformLoc = glGetUniformLocation(shaderProgram.ID, "transform"); // same name as in the exercise5_1.vert. "tramsform"
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		///

		// render container
		vao1.Bind();
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//
		// second container
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = static_cast<GLfloat>(sin(glfwGetTime()));
		transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);// this time take the matrix value
		// now with the uniform matrix being replaced with new transformations, draw it again.
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
void Transformations::Exercise5_2ex1()
{
	initGLFW();
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "Open Glfw and Glad", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}
	// Make the context of our window the current active context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Synchronizes the Frame Rate with the Monitor's Refresh Rate:
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		return;
	}
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Shader 
	Shader shaderProgram("GLSL/exercise5_1.vert", "GLSL/exercise5_1.frag");

	GLfloat vertices[] =
	{
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	// change the texture coords, nth.0f is the nth times the texture will be repeated
	// this is because of the gl_repeat
	GLuint indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	// create EBO and bind and send data
	EBO ebo1(indices, sizeof(indices));

	// size 5 thats why it is 5
	// Position attribute
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
	// Color attribute
	// will start at 3rd index thats why it is 3
	vao1.LinkAttrib(vbo1, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();
	// Texture
	// 1st texture
	GLuint texture1 = 0;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	// S => x-axis, T => y-axis, R => z-axis
	// somce it is 2D texture we are using S and T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	// Flip the image vertically before loading
	stbi_set_flip_vertically_on_load(true);
	GLint width = 0, height = 0, nrChannels = 0;
	unsigned char* data = stbi_load("Resources/Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);


	// 2nd texture
	GLuint texture2 = 0;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the texture
	data = stbi_load("Resources/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);

	// Activate the shader
	shaderProgram.Activate();
	// Tell the shader that the texture is in texture unit 0
	shaderProgram.setInt("texture1", 0); // same name as in the fragment shader like texture1 uniforms
	// Tell the shader that the texture is in texture unit 1
	shaderProgram.setInt("texture2", 1); // same name as in the fragment shader like texture1 uniforms

	// Render loop
	// move
	float x = 0.0f, y = 0.0f;
	while (!glfwWindowShouldClose(window))
	{

		// Process input
		processInput(window, x, y);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix 
		// to identity matrix first
		transform = glm::rotate(transform, static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate the object. x, y, z
		transform = glm::translate(transform, glm::vec3(x, y, 0.0f)); // x , y, z, move the object

		// activate the shader
		// get matrix's uniform location and set matrix
		shaderProgram.Activate();
		GLuint transformLoc = glGetUniformLocation(shaderProgram.ID, "transform"); // same name as in the exercise5_1.vert. "tramsform"
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// render container
		vao1.Bind();
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
void Transformations::Exercise5_1()
{

	initGLFW();
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "Open Glfw and Glad", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return;
	}
	// Make the context of our window the current active context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Synchronizes the Frame Rate with the Monitor's Refresh Rate:
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		return;
	}
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Shader 
	Shader shaderProgram("GLSL/exercise5_1.vert", "GLSL/exercise5_1.frag");

	GLfloat vertices[] =
	{
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	// change the texture coords, nth.0f is the nth times the texture will be repeated
	// this is because of the gl_repeat
	GLuint indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	// create EBO and bind and send data
	EBO ebo1(indices, sizeof(indices));

	// size 5 thats why it is 5
	// Position attribute
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 5* sizeof(GLfloat), (void*)0);
	// Color attribute
	// will start at 3rd index thats why it is 3
	vao1.LinkAttrib(vbo1, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();
	// Texture
	// 1st texture
	GLuint texture1 = 0;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	// S => x-axis, T => y-axis, R => z-axis
	// somce it is 2D texture we are using S and T
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	// Flip the image vertically before loading
	stbi_set_flip_vertically_on_load(true);
	GLint width = 0, height = 0, nrChannels = 0;
	unsigned char* data = stbi_load("Resources/Textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);


	// 2nd texture
	GLuint texture2 = 0;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load and generate the texture
	data = stbi_load("Resources/Textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture\n";
	}
	stbi_image_free(data);

	// Activate the shader
	shaderProgram.Activate();
	// Tell the shader that the texture is in texture unit 0
	shaderProgram.setInt("texture1", 0); // same name as in the fragment shader like texture1 uniforms
	// Tell the shader that the texture is in texture unit 1
	shaderProgram.setInt("texture2", 1); // same name as in the fragment shader like texture1 uniforms

	// Render loop
	// move
	float x = 0.0f, y = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		
		// Process input
		processInput(window, x, y); 

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix 
		// to identity matrix first
		transform = glm::translate(transform, glm::vec3(x, y, 0.0f)); // x , y, z, move the object
		transform = glm::rotate(transform, static_cast<GLfloat>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate the object. x, y, z

		// activate the shader
		// get matrix's uniform location and set matrix
		shaderProgram.Activate();
		GLuint transformLoc = glGetUniformLocation(shaderProgram.ID, "transform"); // same name as in the exercise5_1.vert. "tramsform"
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		
		// render container
		vao1.Bind();
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();

}