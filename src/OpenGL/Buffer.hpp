#ifndef G3_BUFFER_HPP_
#define G3_BUFFER_HPP_

#include "OpenGL.hpp"
#include <memory>

class Buffer {
   public:
      enum Usage :GLenum {
         StaticDraw  =  GL_STATIC_DRAW,
         StaticRead  =  GL_STATIC_READ,
         StaticCopy  =  GL_STATIC_COPY,
         DynamicDraw = GL_DYNAMIC_DRAW,
         DynamicRead = GL_DYNAMIC_READ,
         DynamicCopy = GL_DYNAMIC_COPY,
         StreamDraw  =  GL_STREAM_DRAW,
         StreamRead  =  GL_STREAM_READ,
         StreamCopy  =  GL_STREAM_COPY
      };

      enum Target :GLenum {
         Array                = GL_ARRAY_BUFFER,

         // This is isn't in in Glew 1.6 but is in gl3.h
         #ifdef GL_ATOMIC_COUNTER_BUFFER
            AtomicCounter        = GL_ATOMIC_COUNTER_BUFFER,
         #endif

         CopyRead             = GL_COPY_READ_BUFFER,
         CopyWrite            = GL_COPY_WRITE_BUFFER,
         DrawIndirect         = GL_DRAW_INDIRECT_BUFFER,
         ElementArray         = GL_ELEMENT_ARRAY_BUFFER,
         PixelPack            = GL_PIXEL_PACK_BUFFER,
         PixelUnpack          = GL_PIXEL_UNPACK_BUFFER,
         Texture              = GL_TEXTURE_BUFFER,
         TransformFeedback    = GL_TRANSFORM_FEEDBACK_BUFFER,
         Uniform              = GL_UNIFORM_BUFFER
      };

      Buffer();
      ~Buffer();
      void setTarget(const Target target);
      void bind();
      void bind(const Target target);
      void bindRange(const GLuint& index, const g3::GLintptr& offset, const g3::GLsizeiptr& size);
      void bindBase(const GLuint& index);
      void unbind();
      void data(const Target target, const GLsizei size, const void* data, const Usage usage=StaticDraw);
      void data(const GLsizei size, const void* data, const Usage usage=StaticDraw);
      void subData(const Target& target, const g3::GLintptr& offset, const g3::GLsizeiptr& size, const GLvoid* data);
      void subData(const g3::GLintptr& offset, const g3::GLsizeiptr& size, const GLvoid* data);
      GLsizei getBufferSize() const;
      GLuint getBufferId() const;
      Target getTarget() const;
      void setBufferSize(const GLsizei size);

      static LookupNames TargetNames;
      static LookupNames UsageNames;

   private:
      void bufferData_(const Target target, const GLsizei size, const void* data, const Usage usage=StaticDraw);

      GLuint buffer_id_;
      Target target_;
      GLsizei size_;
      Usage usage_;
};
typedef std::shared_ptr<Buffer> BufferPtr;

inline void Buffer::bind() {
   bind(getTarget());
   logGLError();
}

inline void Buffer::bind(const Target target) {
   if(getTarget() != target) {
      setTarget(target);
   }
   glBindBuffer(target, buffer_id_);
   logGLError();
}

inline void Buffer::setTarget(const Target target) {
   target_ = target;
}

inline void Buffer::unbind() {
   glBindBuffer(target_, 0);
}

inline void Buffer::data(const Target target, const GLsizei size, const void* data, const Usage usage) {
   bufferData_(target, size, data, usage);
}

inline void Buffer::data(const GLsizei size, const void* data, const Usage usage) {
   bufferData_(target_, size, data, usage);
}

inline void Buffer::subData(const Target& target, const g3::GLintptr& offset, const g3::GLsizeiptr& size, const GLvoid* data) {
   bind(target);
   if(offset + size > getBufferSize()) {
      return;
   }
   glBufferSubData(target, offset, size, data);
}

inline void Buffer::subData(const g3::GLintptr& offset, const g3::GLsizeiptr& size, const GLvoid* data) {
   subData(getTarget(), offset, size, data);
}

inline GLsizei Buffer::getBufferSize() const {
   return size_;
}

inline void Buffer::setBufferSize(const GLsizei size) {
   size_ = size;
}

inline GLuint Buffer::getBufferId() const {
   return buffer_id_;
}

inline Buffer::Target Buffer::getTarget() const {
   return target_;
}

inline void Buffer::bufferData_(const Target target, const GLsizei size, const void* data, const Usage usage) {
   setBufferSize(size);
   if(getTarget() != target) {
      setTarget(target);
   }
   usage_ = usage;
   bind();
   glBufferData(target, size, data, usage);
   logGLError();
}

inline void Buffer::bindRange(const GLuint& index, const g3::GLintptr& offset, const g3::GLsizeiptr& size) {
   bind();
   glBindBufferRange(getTarget(), index, getBufferId(), offset, size);
}

inline void Buffer::bindBase(const GLuint& index) {
   glBindBufferBase(getTarget(), index, getBufferId());
}

#endif /* G3_BUFFER_HPP_ */
