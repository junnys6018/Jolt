#Shader Vertex
#version 430 core
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;

out vec3 v_Color;
out vec2 v_TexCoord;

void main()
{
    gl_Position = vec4(a_Position, 0.5, 1.0);
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
}

#Shader Fragment
#version 430 core

out vec4 fragment;
in vec3 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform bool u_UseTexture;

void main()
{
    if (u_UseTexture)
    {
        fragment = texture(u_Texture, v_TexCoord);
    }
    else
    {
        fragment = vec4(v_Color, 1.0);
    }
}