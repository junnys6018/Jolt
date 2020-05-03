#Shader Vertex
#version 430 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(a_Position, 1.0);
}

#Shader Fragment
#version 430 core

out vec4 fragment;
uniform vec3 u_Color;

void main()
{
	fragment = vec4(u_Color, 1.0);
}