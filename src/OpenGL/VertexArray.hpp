#ifndef G3TEST_VERTEXARRAY_HPP_
#define G3TEST_VERTEXARRAY_HPP_

#include <memory>

#include "OpenGL.hpp"
#include "../Debug/console.h"

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

      static void unbind() {
         glBindVertexArray(0);
      }

   private:
      GLuint array_;
};
typedef std::shared_ptr<VertexArray> VertexArrayPtr;

#endif /*  G3TEST_VERTEXARRAY_HPP_ */
