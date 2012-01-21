/*
 * EdgeDetect.frag - A simple Sobel edge detection fragment shader.
 *
 * Written in 2012 by David C. Bishop <david@davidbishop.org>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#version 330

smooth in vec2 UVCoord0;

uniform sampler2D sampler0;
uniform float edge_threshold;
uniform vec2 resolution;
uniform vec4 edge_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
uniform vec4 back_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

layout(location = 0) out vec4 FragColor;

float luma(vec3 color) {
   return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

void main() {
   float dx = 1.0 / float(resolution.x);
   float dy = 1.0 / float(resolution.y);
   
   // If resolution wasn't specified try and calculate it
   if(resolution.x <= 0 || resolution.y <= 0) {
      dx = 1.0 / (gl_FragCoord.x/UVCoord0.x);
      dy = 1.0 / (gl_FragCoord.y/UVCoord0.y);
   }

   float s00 = luma(texture(sampler0, UVCoord0 + vec2(-dx,dy)).rgb);
   float s10 = luma(texture(sampler0, UVCoord0 + vec2(-dx,0.0)).rgb);
   float s20 = luma(texture(sampler0, UVCoord0 + vec2(-dx,-dy)).rgb);
   float s01 = luma(texture(sampler0, UVCoord0 + vec2(0.0,dy)).rgb);
   float s21 = luma(texture(sampler0, UVCoord0 + vec2(0.0,-dy)).rgb);
   float s02 = luma(texture(sampler0, UVCoord0 + vec2(dx, dy)).rgb);
   float s12 = luma(texture(sampler0, UVCoord0 + vec2(dx, 0.0)).rgb);
   float s22 = luma(texture(sampler0, UVCoord0 + vec2(dx, -dy)).rgb);

   float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
   float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);

   float dist = sx * sx + sy * sy;

   if(dist > edge_threshold) {
      FragColor = edge_color;
   } else {
      FragColor = back_color;
   }
}

