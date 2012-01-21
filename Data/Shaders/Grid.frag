/*
 * Grid.frag - Renders a grid pattern.
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

uniform vec4 line_color = vec4(1.0, 1.0, 1.0, 0.2);
uniform vec4 background_color = vec4(0.3, 0.3, 0.5, 1.0);
uniform int num_lines = 10;
uniform float line_width = 0.01;

layout(location = 0) out vec4 FragColor;

void main() {
   float line_spacing = 1.0/(num_lines-1);
   float half_width = line_width/2;
   float xmod = mod(UVCoord0.x, line_spacing);
   float ymod = mod(UVCoord0.y, line_spacing);

   FragColor += background_color * background_color.a;

   if(xmod > line_spacing - half_width) {
      FragColor += line_color * line_color.a;
   } else if(ymod > line_spacing - half_width) {
      FragColor += line_color * line_color.a;
   } else if(UVCoord0.x <= half_width) {
      FragColor += line_color * line_color.a;
   } else if(UVCoord0.y <= half_width) {
      FragColor += line_color * line_color.a;
   }
}

