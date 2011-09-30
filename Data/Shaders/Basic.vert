#version 330 compatibility

in      vec4 Position;
in      vec3 Normal;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

out vec2 MCPosition;
smooth out vec3 VaryingNormal;
smooth out vec3 VaryingLightDir;

struct light {
   vec4 position;
};
uniform light Lights[8];

void main()
{
   VaryingNormal = NormalMatrix * Normal;
   vec4 Position4 = MVMatrix * Position;
   vec3 Position3 = Position4.xyz / Position4.w;
   VaryingLightDir = normalize(Lights[0].position.xyz - Position3);

   gl_Position = MVPMatrix * Position;
}
