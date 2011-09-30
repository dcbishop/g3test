#include "Cube.hpp"

#include <vector>
using std::vector;


#include "../Debug/console.h"

bool Cube::isInitilized_ = false;

Cube::Cube() {
   if(!isInitilized_) {
      init();
   }
   logGLError();
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
      rtf, ltf, lbf, rbf, rtf, lbf, // Front
      rtb, lbb, ltb, rbb, lbb, rtb, // Back
      ltf, ltb, lbb, ltf, lbb, lbf, // Left 
      rtb, rtf, rbf, rbb, rtb, rbf, // Right
      ltf, rtf, rtb, rtb, ltb, ltf, // Top
      rbb, rbf, lbf, lbf, lbb, rbb  // Bottom
   };

   array_.bind();
   logGLError();
   buffer_.bind();
   logGLError();
   buffer_.data(vertices.size()*sizeof(vec3), &vertices[0][0]);
   glVertexAttribPointer(AttributeIndex::Vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
   logGLError();
   glEnableVertexAttribArray(AttributeIndex::Vertex);
   logGLError();
   isInitilized_ = true;
}

void Cube::deinit() {
   isInitilized_ = false;
}

void Cube::render() {
   logGLError();
   array_.bind();
   logGLError();
   glDrawArrays(GL_TRIANGLES, 0, buffer_.getSize());
   logGLError();
}
