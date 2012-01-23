/*
 * UBODummy.vert - A helper shader for the Uniform Block Object stuff to use.
 * allows quering uniform block information only avilable from a compiled
 * shader.
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
#pragma optimize(off)

layout(std140) uniform SharedUniforms {
   mat4 MVMatrix;
   mat4 ProjectionMatrix;
   mat4 MVPMatrix;
   mat3 NormalMatrix;
   vec2 resolution;
   float time;
};

void main() {}
