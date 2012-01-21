/*
 * FlatTexture.vert - Vertex shader that only passes through raw position and
 * texture cordinates. Performs no vertex matrix transformations or lighting
 * calculations.
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

layout(location = 0) in vec4 Position;
layout(location = 8) in vec2 TexCoord0;

smooth out vec2 UVCoord0;

void main() {
   gl_Position = Position;
   UVCoord0 = TexCoord0;
}
