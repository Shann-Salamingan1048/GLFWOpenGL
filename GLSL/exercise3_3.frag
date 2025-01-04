#version 330 core
out vec4 FragColor; // we need to declare an output for the fragment shader
in vec3 ourColor; // the input variable from the vertex shader (same name and same type) in  exercise3_2.vert
// if you do "ourColors" instead of "ourColor" in the main function, the color will be black or white 
void main()
{
	FragColor = vec4(ourColor, 1.0);
}