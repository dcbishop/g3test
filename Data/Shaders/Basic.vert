#version 330

layout( location = 0 ) in vec4 Position;
layout( location = 2 ) in vec3 Normal;
layout( location = 3 ) in vec3 Color;
layout( location = 8 ) in vec3 TexCoord0;

layout(std140) uniform SharedUniforms {
   mat4 MVMatrix;
   mat4 ProjectionMatrix;
   mat4 MVPMatrix;
   mat4 ViewportMatrix;
   mat3 NormalMatrix;
   vec2 resolution;
   float time;
};

smooth out vec3 VNormal;
smooth out vec4 VColor;
smooth out vec2 VTexCoord0;
smooth out vec3 VLightDir;

void main() {
   VNormal = NormalMatrix * Normal;
   vec4 Position4 = MVMatrix * Position;
   vec3 Position3 = Position4.xyz / Position4.w;
   vec3 light_pos = vec3(1.0, 1.0, 1.0); // [TODO]: Bind lights
   VLightDir = normalize(light_pos - Position3);

   gl_Position = MVPMatrix * Position;
   VColor = vec4(Color, 1.0f);
   VTexCoord0 = TexCoord0;
}
