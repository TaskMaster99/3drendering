#version 460 core
out vec4 FragColor;
in vec4 vertexColor; 

uniform vec3 lightColor;
uniform vec3 objectColor; 

void main()
{
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    FragColor = vec4(ambient * objectColor , 1.0);
}