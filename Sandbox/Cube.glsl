#Shader Vertex
#version 430 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 1.0);
}

#Shader Fragment
#version 430 core

out vec4 fragment;

void main()
{
    fragment = vec4(0.8, 0.0, 0.8, 1.0);
}