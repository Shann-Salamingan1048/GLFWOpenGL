#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float mixValue; // the same name as in the C++ code 
// texture samplers
uniform sampler2D texture1; // = 0, container
uniform sampler2D texture2; // = 1, awesomeface

void main()
{
	// linearly interpolate between both textures (1.f - mixValue  container, mixValue awesomeface) in percentages
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}

