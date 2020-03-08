#Shader Vertex
#version 430 core
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

out vec3 v_Color;

void main()
{
    gl_Position = vec4(a_Position, 0.5, 1.0);
	v_Color = a_Color;
}

#Shader Fragment
#version 430 core

out vec4 fragment;
in vec3 v_Color;

void main()
{
    fragment = vec4(v_Color, 1.0);
}