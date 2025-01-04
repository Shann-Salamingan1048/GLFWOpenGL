#include "Exercises.h"
void Exercises::initGLFW()
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
void Exercises::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// if the user resizes the window, the viewport should be adjusted as well
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void Exercises::processInput(GLFWwindow* window)
{
	// if the user presses the space key, the window should close
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void Exercises::shaderExercise3_5()
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
	Shader shaderProgram("GLSL/exercise3_5.vert", "GLSL/exercise3_5.frag");

	GLfloat vertices[] =
	{							/// colors
		 // positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader
		shaderProgram.Activate();
		vao1.Bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
void Exercises::shaderExercise3_4()
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
	Shader shaderProgram("GLSL/exercise3_4.vert", "GLSL/exercise3_4.frag");

	GLfloat vertices[] =
	{							/// colors
		// first triangle
		-0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
		-0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// right
		-0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// left
		 0.9f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// right
		 0.45f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f// top 
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();
	
	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader
		shaderProgram.Activate();
		float offset = 1.0f;
		shaderProgram.setFloat("xOffset", offset); // set the value of the uniform xOffset to 0.5f. This will move the triangle to the right side of the screen.
		// set the value of the uniform named "xOffset" in the vertex shader to 0.5f. This will move the triangle to the right side of the screen.

		vao1.Bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
void Exercises::shaderExercise3_3()
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
	Shader shaderProgram("GLSL/exercise3_3.vert", "GLSL/exercise3_3.frag");

	GLfloat vertices[] =
	{							/// colors
		// first triangle
		-0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
		-0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// right
		-0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// left
		 0.9f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// right
		 0.45f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f// top 
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0); 
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); 
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader
		shaderProgram.Activate();
		vao1.Bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();

}
void Exercises::shaderInterpolation3_2()
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
	//Load GLAD so it configures OpenGL
	//gladLoadGL(); redundant
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
	Shader shaderProgram("GLSL/exercise3_2.vert", "GLSL/exercise3_2.frag");

	GLfloat vertices[] =
	{							/// colors
		// first triangle
		-0.9f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
		-0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// right
		-0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// left
		 0.9f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// right
		 0.45f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f// top 
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	/*
		Vertex 1				Vertex 2				Vertex 3
		X  Y  Z  R  G  B 	 X  Y  Z  R  G  B       X  Y  Z  R  G  B
		0  4  8  12 16 20    24 28 32 36 40 44      48 52 56 60 64 68
Pos:    | Stride: 24 -------->|		  |
	- Offset: 0	 |					  |
Color            |:---- Stride: 24 --->
	- Offset: 12-|
	0 -> 12 or from 0 -> 12
	*/
	// Configure vertex attributes
	// the color size is 3 floats
	// 6 * sizeof(GLfloat) is the stride ==> 6 * 4 = 24 bytes
	// the position vertex arrtibute is first so we declare an offset of 0 => (void*)0
	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0); // position and it can connected to the vertex shader exercise3_2.vert
	// the color vertex arrtibute is second so we declare an offset of 3 * sizeof(GLfloat) => (void*)(3 * sizeof(GLfloat)) => 3 * 4 = 12 bytes
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // color and it can connected to the vertex shader exercise3_2.vert
	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader
		shaderProgram.Activate();
		vao1.Bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();

}
void Exercises::shaderUniforms3_1()
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
	//Load GLAD so it configures OpenGL
	//gladLoadGL(); redundant
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
	Shader shaderProgram("default.vert", "default.frag");

	GLfloat vertices[] =
	{
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));


	// Configure vertex attributes
	vao1.LinkAttrib(vbo1, 0);

	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader
		shaderProgram.Activate();
		GLfloat timeVal = glfwGetTime(); // will get the time in seconds
		// GLfloat greenVal = static_cast<GLfloat>((sin(timeVal) / 2) + 0.5); // will change the green value from 0 to 1
		GLfloat greenVal = (sin(timeVal) / 2) + 0.5; // will change the green value from 0 to 1
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColorDawKuno"); // will find location of the uniform named ourColorDawKuno in the default.frag
		glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f); // set the value of the uniform ourColorDawKuno to a green color

		vao1.Bind();
		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
void Exercises::helloTriangle2_5()
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
	//Load GLAD so it configures OpenGL
	//gladLoadGL(); redundant
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
	Shader shaderProgram("default.vert", "Fragments/Orange.frag"); // orange
	Shader shaderProgram2;
	shaderProgram2.fragShadeOnly("Fragments/Yellow.frag"); // yellow
	GLfloat vertices1[] =
	{
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 

	};
	GLfloat vertices2[] =
	{
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};
	// Create and bind Vertex Array Object (VAO)
	// Create and bind Vertex Buffer Object (VBO)
	// Configure vertex attributes
	// Unbind All Buffers
	// by order matters
	VAO Vaos[2];
	VBO Vbos[2] = { VBO(vertices1, sizeof(vertices1)), VBO(vertices2, sizeof(vertices2)) };
	Vaos[0].Bind();
	Vaos[0].LinkAttrib(Vbos[0], 0);
	Vaos[0].Unbind();
	Vbos[0].Unbind();

	Vaos[1].Bind();
	Vaos[1].LinkAttrib(Vbos[1], 0);
	Vaos[1].Unbind();
	Vbos[1].Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		shaderProgram.Activate();
		Vaos[0].Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shaderProgram2.Activate();
		Vaos[1].Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Vaos[0].Delete();
	Vbos[0].Delete();
	Vaos[1].Delete();
	Vbos[1].Delete();
	shaderProgram.Delete();
	shaderProgram2.Delete();
	glfwTerminate();
}
void Exercises::helloTriangle2_4()
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
	//Load GLAD so it configures OpenGL
	//gladLoadGL(); redundant
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
	Shader shaderProgram("default.vert", "default.frag");
	GLfloat vertices1[] =
	{
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 

	};
	GLfloat vertices2[] =
	{
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};
	// Create and bind Vertex Array Object (VAO)
	// Create and bind Vertex Buffer Object (VBO)
	// Configure vertex attributes
	// Unbind All Buffers
	// by order matters
	VAO Vaos[2];
	VBO Vbos[2] = { VBO(vertices1, sizeof(vertices1)), VBO(vertices2, sizeof(vertices2)) };
	Vaos[0].Bind();
	Vaos[0].LinkAttrib(Vbos[0], 0);
	Vaos[0].Unbind();
	Vbos[0].Unbind();

	Vaos[1].Bind();
	Vaos[1].LinkAttrib(Vbos[1], 0);
	Vaos[1].Unbind();
	Vbos[1].Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		shaderProgram.Activate();
		Vaos[0].Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Vaos[1].Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Vaos[0].Delete();
	Vbos[0].Delete();
	Vaos[1].Delete();
	Vbos[1].Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
void Exercises::helloTriangle2_3()
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
	//Load GLAD so it configures OpenGL
	//gladLoadGL(); redundant
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
	Shader shaderProgram("default.vert", "default.frag");

	GLfloat vertices[] = 
	{
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};
	// Create and bind Vertex Array Object (VAO)
	VAO vao1;
	vao1.Bind();

	// Create and bind Vertex Buffer Object (VBO)
	VBO vbo1(vertices, sizeof(vertices));
	

	// Configure vertex attributes
	vao1.LinkAttrib(vbo1, 0);

	// Unbind All Buffers
	vao1.Unbind();
	vbo1.Unbind();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Process input
		processInput(window);

		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		shaderProgram.Activate();
		vao1.Bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	shaderProgram.Delete();
	glfwTerminate();
}
