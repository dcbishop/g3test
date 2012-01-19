#version 330

smooth in vec4 FlatColor;
smooth in vec3 VaryingNormal;
smooth in vec3 VaryingLightDir;

layout(location = 0) out vec4 FragColor;

struct matrial {
   vec4 diffuseColor;
   vec4 ambientColor;
};

uniform matrial material;
uniform vec4 color_overide;

void main() {
   vec4 ambientColor = vec4(0.0, 0.0, 0.0, 1.0);
   float diffuse_intensity = max(0.0, dot(normalize(VaryingNormal), normalize(VaryingLightDir)));
   FragColor = diffuse_intensity * (material.diffuseColor + FlatColor);
   FragColor += ambientColor;
   vec3 reflection = normalize(reflect(-normalize(VaryingLightDir), normalize(VaryingNormal)));
   float spec = max(0.0, dot(normalize(VaryingNormal), reflection));

   if(diffuse_intensity != 0) {
      float fspec = pow(spec, 128.0);
      FragColor.rgb += vec3(fspec, fspec, fspec);

   }

   if(color_overide.a != 0.0) {
      FragColor=color_overide;
   }
}
