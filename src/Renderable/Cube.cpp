#include "Cube.hpp"

#include "../Debug/console.h"

#include "../OpenGL/Shader.hpp"
#include "../OpenGL/Program.hpp"


bool Cube::isInitilized_ = false;

Cube::Cube() {
   if(!isInitilized_) {
      init();
   }
   
}

Cube::~Cube() {
   deinit();
}

void Cube::init() {
   using glm::vec3;

   position_ = vec3(0.0, 0.0, 0.0);
   
   GLfloat p = CUBE_SIZE / 2.0f;
   GLfloat n = -p;

   // Vertices   
   vec3 rtf(p, p, p);
   vec3 rtb(p, p, n);
   vec3 rbf(p, n, p);
   vec3 rbb(p, n, n);
   vec3 ltf(n, p, p);
   vec3 ltb(n, p, n);
   vec3 lbf(n, n, p);
   vec3 lbb(n, n, n);

   // Normals
   vec3 nf(0.0f, 0.0f, 1.0f);
   vec3 nb(0.0f, 0.0f, -1.0f);
   vec3 nu(0.0f, 1.0f, 0.0f);
   vec3 nd(0.0f, -1.0f, 0.0f);
   vec3 nl(-1.0, 0.0f, 0.0f);
   vec3 nr(1.0, 0.0f, 0.0f);

   // C++11 only!
   vector<vec3> vertices {
      lbf, ltf, rtf, lbf, rtf, rbf // Front
   };

   buffer_.bind();
   buffer_.data(vertices.size()*sizeof(vec3), &vertices[0][0]);

   isInitilized_ = true;
   
   Shader vertex_shader_(Shader::Vertex);
   Program program_;
}

void Cube::deinit() {
   isInitilized_ = false;
}

void Cube::render() {
   int shaderAtribute = 0; // TODO: Bind to vertex shader, 0 is legacy fixed function
   buffer_.bind();
   glVertexAttribPointer(shaderAtribute, 3, GL_FLOAT, GL_FALSE, 0, 0);  
   glEnableVertexAttribArray(shaderAtribute);
   glDrawArrays(GL_TRIANGLES, 0, buffer_.getSize());
}
