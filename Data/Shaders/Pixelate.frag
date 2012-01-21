/*
 * Pixelate.frag - A pixelation fragment shader.
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

layout(location = 0) out vec4 FragColor;

uniform float time = 0.0;
uniform float speed = 1.0;
uniform int resolution_min = 50;
uniform int resolution_max = 200;

float pi = 3.14159;

void main() {
   float gridsize = resolution_min+abs(mod(time*speed, 2.0)-1.0)*(resolution_max-resolution_min);
   vec2 uvcord;
   uvcord.x = floor(UVCoord0.x*gridsize)/gridsize;
   uvcord.y = floor(UVCoord0.y*gridsize)/gridsize;
   FragColor = texture2D(sampler0, uvcord);
}

