#version 460 core
out vec4 FragColor;

in vec3 Color;

in vec2 Uv;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, Uv);
}