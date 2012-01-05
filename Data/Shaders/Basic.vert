#version 330

layout(location = 0) in vec4 Position;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Color;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

out vec2 PositionXY;
smooth out vec3 VaryingNormal;
smooth out vec3 VaryingLightDir;
smooth out vec3 FlatColor;

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
   FlatColor = Color;
   PositionXY = gl_Position.xy;
}
