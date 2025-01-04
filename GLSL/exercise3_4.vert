#version 330 core
 
layout(location = 0) in vec3 aPos; // the position variable has attribute position 0
layout(location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor;

uniform float xOffset; // uniform variable for x offset
void main()
{
	gl_Position = vec4(aPos.x + xOffset,aPos.y, aPos.z, 1.0);
	ourColor = aColor;
}