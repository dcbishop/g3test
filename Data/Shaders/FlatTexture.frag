/*
 * FlatTexture.vert - Vertex shader that only outputs a texture color. Performs
 * no lighting calculations.
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

smooth in vec2 VTexCoord0;

uniform sampler2D tex0;

layout( location = 0 ) out vec4 Color;

void main() {
   Color = texture2D(tex0, VTexCoord0);
}
