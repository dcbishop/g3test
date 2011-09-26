#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

#include <GL3/gl3.h>

const GLfloat CUBE_SIZE = 1.0f;

class VertexArray {
   public:
      VertexBufferObject() {
         glGenVertexArrays(1, &array_);
         
      }
      
      ~VertexBufferObject() {
         glDeleteVertexArrays(1, &array_);
      }
      
      void bind() {
         glBindVertexArray(array_);
      }

   private:
      GLuint array_;
};

#endif /*  VERTEXARRAY_HPP_ */
