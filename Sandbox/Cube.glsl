#Shader Vertex
#version 430 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 v_Normal;
out vec3 v_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(a_Position, 1.0);
	v_Normal = mat3(transpose(inverse(u_View * u_Model))) * a_Normal;
	v_Position = (u_View * u_Model * vec4(a_Position, 1.0)).xyz;
}

#Shader Fragment
#version 430 core

out vec4 fragment;

in vec3 v_Normal;
in vec3 v_Position;

uniform vec3 u_Warm;
uniform vec3 u_Cool;
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;

void main()
{
	vec3 normal = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_Position);
	vec3 viewDir = normalize(-v_Position);

	float val = 0.5 * (dot(normal, lightDir) + 1.0);
	vec3 color = mix(u_Cool, u_Warm, val);
	
	vec3 reflected = reflect(-lightDir, normal);
	float specular = dot(reflected, viewDir);
	specular = pow(clamp(specular, 0.0, 1.0), 8);

	color = mix(color, u_LightColor, specular);

	fragment = vec4(color, 1.0);
}