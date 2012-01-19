#ifndef G3TEST_VERTEXARRAY_HPP_
#define G3TEST_VERTEXARRAY_HPP_

#include <memory>

#include "OpenGL.hpp"
#include "../Debug/console.h"

class VertexArray {
   public:
      enum Mode: GLenum {
         Points =                   GL_POINTS,
         LineStrip =                GL_LINE_STRIP,
         LineLoop =                 GL_LINE_LOOP,
         Lines =                    GL_LINES,
         LineStripAdjacency =       GL_LINE_STRIP_ADJACENCY,
         LinesAdjacency =           GL_LINES_ADJACENCY,
         TriangleStrip =            GL_TRIANGLE_STRIP,
         TriangleFan =              GL_TRIANGLE_FAN,
         Triangles =                GL_TRIANGLES,
         TriangleStripAdjacency =   GL_TRIANGLE_STRIP_ADJACENCY,
         TrianglesAdjancey =        GL_TRIANGLES_ADJACENCY,
         Patches =                  GL_PATCHES
      };

      VertexArray();      
      ~VertexArray();
      void bind() const;
      static void unbind();
      void draw() const;
      void draw(Mode mode, GLint first, GLsizei count) const;


      void setMode(const Mode mode);
      void setCount(const GLsizei count);
      Mode getMode() const;
      GLsizei getCount() const;

   private:
      GLuint array_;
      Mode mode_;
      GLsizei count_;
};
typedef std::shared_ptr<VertexArray> VertexArrayPtr;

inline VertexArray::VertexArray() {
	glGenVertexArrays(1, &array_);
   mode_ = Triangles;
   count_ = 0;
}

inline VertexArray::~VertexArray() {
   glDeleteVertexArrays(1, &array_);
}

inline void VertexArray::bind() const {
   glBindVertexArray(array_);
}

inline void VertexArray::unbind() {
   glBindVertexArray(0);
}

inline void VertexArray::draw() const {
   bind();
   draw(mode_, 0, count_);
}

inline void VertexArray::draw(Mode mode, GLint first, GLsizei count) const {
   bind();
   glDrawArrays(mode, first, count);
}

inline void VertexArray::setMode(const Mode mode) {
   mode_ = mode;   
}

inline void VertexArray::setCount(const GLsizei count) {
   count_ = count;
}

inline VertexArray::Mode VertexArray::getMode() const {
   return mode_;
}

inline GLsizei VertexArray::getCount() const {
   return count_;
}

#endif /*  G3TEST_VERTEXARRAY_HPP_ */
