#version 330 core
out vec4 FragColor; // output color of our fragment shader

in vec3 ourColor; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord; // the input variable from the vertex shader (same name and same type)

// texture sampler
uniform sampler2D texture1; // we use the previously defined texture unit 0

void main()
{
	FragColor = texture(texture1, TexCoord);
}