#version 330

layout(location = 0) in vec4 Position;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Color;
layout(location = 8) in vec3 TexCoord0;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

smooth out vec3 VaryingNormal;
smooth out vec3 VaryingLightDir;
smooth out vec4 FlatColor;
smooth out vec2 UVCoord0;

struct light {
   vec4 position;
};
uniform light Lights[8];

void main() {
   VaryingNormal = NormalMatrix * Normal;
   vec4 Position4 = MVMatrix * Position;
   vec3 Position3 = Position4.xyz / Position4.w;
   VaryingLightDir = normalize(/*Lights[0].position.xyz*/ vec3(1.0, 1.0, 1.0) - Position3); // TODO: Bind lights

   gl_Position = MVPMatrix * Position;
   FlatColor = vec4(Color, 1.0f);
   
   UVCoord0 = TexCoord0.st;
}
