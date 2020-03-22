#Shader Vertex
#version 430 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 v_Normal;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(a_Position, 1.0);
	v_Normal = a_Normal;
}

#Shader Fragment
#version 430 core

out vec4 fragment;
in vec3 v_Normal;

void main()
{
    fragment = vec4(0.5 * (normalize(v_Normal) + vec3(1.0)), 1.0);
}