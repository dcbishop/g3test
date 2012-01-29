#ifndef G3TEST_VERTEXARRAY_HPP_
#define G3TEST_VERTEXARRAY_HPP_

#include <memory>

#include "OpenGL.hpp"
#include "../Debug/console.h"

class VertexArray {
   public:
      enum Mode: GLenum {
         Points                  = GL_POINTS,
         LineStrip               = GL_LINE_STRIP,
         LineLoop                = GL_LINE_LOOP,
         Lines                   = GL_LINES,
         LineStripAdjacency      = GL_LINE_STRIP_ADJACENCY,
         LinesAdjacency          = GL_LINES_ADJACENCY,
         TriangleStrip           = GL_TRIANGLE_STRIP,
         TriangleFan             = GL_TRIANGLE_FAN,
         Triangles               = GL_TRIANGLES,
         TriangleStripAdjacency  = GL_TRIANGLE_STRIP_ADJACENCY,
         TrianglesAdjancey       = GL_TRIANGLES_ADJACENCY,
         Patches                 = GL_PATCHES
      };
      
      enum Type: GLenum {
         Unsignedbyte            = GL_UNSIGNED_BYTE,
         UnsignedShort           = GL_UNSIGNED_SHORT,
         UnsignedInt             = GL_UNSIGNED_INT
      };

      VertexArray();      
      ~VertexArray();
      void bind() const;
      static void unbind();
      void draw() const;
      void draw(const Mode mode, const GLint first, const GLsizei count) const;
      void drawElements() const;
      void drawElements(const Mode mode, const GLsizei count, const Type type, const GLvoid* indices = nullptr) const;

      void setMode(const Mode mode);
      void setCount(const GLsizei count);
      void setType(const Type type);
      Mode getMode() const;
      Type getType() const;
      GLsizei getCount() const;

   private:
      GLuint array_;
      Mode mode_;
      GLsizei count_;
      Type type_;
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
   draw(getMode(), 0, getCount());
}

inline void VertexArray::draw(Mode mode, GLint first, GLsizei count) const {
   bind();
   glDrawArrays(mode, first, count);
}

inline void VertexArray::drawElements() const {
   drawElements(getMode(), getCount(), getType());
}

inline void VertexArray::drawElements(const Mode mode, const GLsizei count, const Type type, const GLvoid* indices) const {
   bind();
   glDrawElements(mode, count, type, indices);
}

inline void VertexArray::setMode(const Mode mode) {
   mode_ = mode;   
}

inline void VertexArray::setCount(const GLsizei count) {
   count_ = count;
}

inline void VertexArray::setType(const Type type) {
   type_ = type;
}

inline VertexArray::Mode VertexArray::getMode() const {
   return mode_;
}

inline GLsizei VertexArray::getCount() const {
   return count_;
}

inline VertexArray::Type VertexArray::getType() const {
   return type_;
}

#endif /*  G3TEST_VERTEXARRAY_HPP_ */
