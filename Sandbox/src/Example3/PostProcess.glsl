#Shader Vertex
#version 430 core
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 0.5, 1.0);
	v_TexCoord = a_TexCoord;
}

#Shader Fragment
#version 430 core

out vec4 fragment;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform bool u_PostProcess;
const float offset = 1.0 / 400.0; 

void main()
{
	if (u_PostProcess)
	{
		vec2 offsets[9] = vec2[](
			vec2(-offset,  offset), // top-left
			vec2( 0.0f,    offset), // top-center
			vec2( offset,  offset), // top-right
			vec2(-offset,  0.0f),   // center-left
			vec2( 0.0f,    0.0f),   // center-center
			vec2( offset,  0.0f),   // center-right
			vec2(-offset, -offset), // bottom-left
			vec2( 0.0f,   -offset), // bottom-center
			vec2( offset, -offset)  // bottom-right    
		);

		float kernel[9] = float[](
			1.0,  1.0, 1.0,
			1.0, -8.0, 1.0,
			1.0,  1.0, 1.0
		);
 
		vec3 sampleTex[9];
		for(int i = 0; i < 9; i++)
		{
			sampleTex[i] = vec3(texture(u_Texture, v_TexCoord.st + offsets[i]));
		}
		vec3 col = vec3(0.0);
		for(int i = 0; i < 9; i++)
			col += sampleTex[i] * kernel[i];
		fragment = vec4(col, 1.0);
	}
	else
	{
		fragment = texture(u_Texture, v_TexCoord);
	}
}