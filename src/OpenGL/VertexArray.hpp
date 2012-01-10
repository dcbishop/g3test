#ifndef G3TEST_VERTEXARRAY_HPP_
#define G3TEST_VERTEXARRAY_HPP_

#include <memory>

#include "OpenGL.hpp"
#include "../Debug/console.h"

class VertexArray {
   public:
      VertexArray();      
      ~VertexArray();
      void bind();
      static void unbind();

   private:
      GLuint array_;
};
typedef std::shared_ptr<VertexArray> VertexArrayPtr;

inline VertexArray::VertexArray() {
	glGenVertexArrays(1, &array_);
}

inline VertexArray::~VertexArray() {
   glDeleteVertexArrays(1, &array_);
}

inline void VertexArray::bind() {
   glBindVertexArray(array_);
}

inline void VertexArray::unbind() {
   glBindVertexArray(0);
}

#endif /*  G3TEST_VERTEXARRAY_HPP_ */
