#ifndef G3TEST_VERTEXARRAY_HPP_
#define G3TEST_VERTEXARRAY_HPP_

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

#include "../Debug/console.h"

const GLfloat CUBE_SIZE = 1.0f;

class VertexArray {
   public:
      VertexArray() {
         glGenVertexArrays(1, &array_);
         
      }
      
      ~VertexArray() {
         glDeleteVertexArrays(1, &array_);
      }
      
      void bind() {
         glBindVertexArray(array_);
      }

   private:
      GLuint array_;
};

#endif /*  G3TEST_VERTEXARRAY_HPP_ */
