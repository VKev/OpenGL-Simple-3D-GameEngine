#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 aNormal;

out vec3 Color;
out vec2 Uv;
out vec3 Normal;
out vec3 crntPos;


uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
   crntPos = vec3(model * vec4(aPos,1.0));
   gl_Position = camMatrix * vec4(crntPos, 1.0);
   Color = aColor;
   Uv = uv;
   Normal = aNormal;
}