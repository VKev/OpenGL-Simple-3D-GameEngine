#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 uv;

out vec3 Color;
out vec2 Uv;

uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x*scale ,aPos.y* scale, aPos.z *scale, 1.0);
   Color = aColor;
   Uv = uv;
}