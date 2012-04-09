#version 330

smooth in vec4 VColor;
smooth in vec3 VNormal;
smooth in vec2 VTexCoord0;
smooth in vec3 VLightDir;

layout( location = 0 ) out vec4 Color;

struct matrial {
   vec4 diffuseColor;
   vec4 ambientColor;
};

uniform matrial material;
uniform vec4 color_overide;
uniform sampler2D tex0;

void main() {
   vec4 ambientColor = vec4(0.0, 0.0, 0.0, 1.0);
   vec4 texcol = texture2D(tex0, VTexCoord0);

   float diffuse_intensity = max(0.0, dot(normalize(VNormal), normalize(VLightDir)));
   Color = diffuse_intensity * (material.diffuseColor + VColor);
   Color += ambientColor;
   Color += texcol * texcol.a;

   vec3 reflection = normalize(reflect(-normalize(VLightDir), normalize(VNormal)));
   float spec = max(0.0, dot(normalize(VNormal), reflection));

   if(diffuse_intensity != 0) {
      float fspec = pow(spec, 128.0);
      Color.rgb += vec3(fspec, fspec, fspec);
   }

   if(color_overide.a != 0.0) {
      Color = color_overide;
   }
}
