#ifndef G3_BUFFER_HPP_
#define G3_BUFFER_HPP_

#include "OpenGL.hpp"
#include <memory>

class Buffer {
   public:
      enum Usage :GLenum {
         StaticDraw =  GL_STATIC_DRAW,
         StaticRead =  GL_STATIC_READ,
         StaticCopy =  GL_STATIC_COPY,
         DynamicDraw = GL_DYNAMIC_DRAW,
         DynamicRead = GL_DYNAMIC_READ,
         DynamicCopy = GL_DYNAMIC_COPY,
         StreamDraw =  GL_STREAM_DRAW,
         StreamRead =  GL_STREAM_READ,
         StreamCopy =  GL_STREAM_COPY
      };

      enum Target :GLenum {
         Array =              GL_ARRAY_BUFFER,
         AtomicCounter =      GL_ATOMIC_COUNTER_BUFFER,
         CopyRead =           GL_COPY_READ_BUFFER,
         CopyWrite =          GL_COPY_WRITE_BUFFER,
         DrawIndirect =       GL_DRAW_INDIRECT_BUFFER,
         ElementArray =       GL_ELEMENT_ARRAY_BUFFER,
         PixelPack =          GL_PIXEL_PACK_BUFFER,
         PixelUnpack =        GL_PIXEL_UNPACK_BUFFER,
         Texture =            GL_TEXTURE_BUFFER,
         TransformFeedback =  GL_TRANSFORM_FEEDBACK_BUFFER,
         Uniform =            GL_UNIFORM_BUFFER
      };

      Buffer();
      ~Buffer();
      void setTarget(const Target target);
      void bind();
      void bind(const Target target);
      void unbind();
      void data(const Target target, const GLsizei size, const void* data, const Usage usage=StaticDraw);
      void data(const GLsizei size, const void* data, const Usage usage=StaticDraw);
      GLsizei getSize() const;

   private:
      void bufferData_(const Target target, const GLsizei size, const void* data, const Usage usage=StaticDraw);

      GLuint buffer_id_;
      Target target_;
      GLsizei size_;
      Usage usage_;
};
typedef std::shared_ptr<Buffer> BufferPtr;

inline void Buffer::bind() {
   bind(target_);
   logGLError();
}

inline void Buffer::bind(const Target target) {
   DEBUG_H("Binding buffer %d", buffer_id_);
   glBindBuffer(target, buffer_id_);
   target_ = target;
   logGLError();
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

inline GLsizei Buffer::getSize() const {
   return size_;
}

inline void Buffer::bufferData_(const Target target, const GLsizei size, const void* data, const Usage usage) {
   bind();
   size_ = size;
   target_ = target;
   usage_ = usage;
   glBufferData(target, size, data, usage);
   logGLError();
}

#endif /* G3_BUFFER_HPP_ */
