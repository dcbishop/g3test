/*
 * TextureTunnel.frag - Renders a texture using a tunnel effect.
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

uniform float time = 0.0f;
uniform float speed = 0.25f;
uniform float rotate_speed = 0.25f;
uniform float fish_eye = 0.1;

layout(location = 0) out vec4 FragColor;

float pi = 3.14159;

void main() {
   vec2 uvcord = UVCoord0;
   vec2 p = -1.0 + 2.0 * UVCoord0;
   float angle = atan(p.x, p.y);
   float radius = sqrt(dot(p,p));
   uvcord.x = time*speed + fish_eye/radius;
   uvcord.y = angle/pi + time*rotate_speed;
   FragColor = texture2D(sampler0, uvcord);
}

