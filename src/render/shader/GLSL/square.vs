#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor; 

uniform mat4 projectionM;
uniform mat4 modelM;
uniform mat4 rotM;

void main()
{
    gl_Position = projectionM * modelM * rotM* vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aColor, 1.0f);
}