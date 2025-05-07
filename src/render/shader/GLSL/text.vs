#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexPos;

out vec2 textCoord; 

uniform mat4 projectionM;
uniform mat4 modelM;
uniform mat4 rotM;

void main()
{
    gl_Position = projectionM * modelM * rotM* vec4(aPos.x, aPos.y, aPos.z, 1.0);
    textCoord = aTexPos;
}