#version 460 core
out vec4 FragColor;

in vec3 Color;
in vec2 Uv;
in vec3 Normal;
in vec3 crntPos;


uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambientLight = 0.2;
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - crntPos);
	
	float deffuseLight = max(dot( normal, lightDir), 0.0f);

	float specularLight = 1.0f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	specularLight = specAmount * specularLight;


	FragColor = texture(tex0, Uv)*lightColor *(deffuseLight + ambientLight + specularLight);
}