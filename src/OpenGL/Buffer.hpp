#ifndef G3_BUFFER_HPP_
#define G3_BUFFER_HPP_

class Buffer {
   public:
      enum Usage :GLenum {
         StaticDraw = GL_STATIC_DRAW,
         StaticRead = GL_STATIC_READ,
         StaticCopy = GL_STATIC_COPY,
         DynamicDraw = GL_DYNAMIC_DRAW,
         DynamicRead = GL_DYNAMIC_READ,
         DynamicCopy = GL_DYNAMIC_COPY,
         StreamDraw = GL_STREAM_DRAW,
         StreamRead = GL_STREAM_READ,
         StreamCopy = GL_STREAM_COPY
      };

      enum Target :GLenum {
         Array = GL_ARRAY_BUFFER,
         AtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
         CopyRead = GL_COPY_READ_BUFFER,
         CopyWrite = GL_COPY_WRITE_BUFFER,
         DrawIndirect = GL_DRAW_INDIRECT_BUFFER,
         ElementArray = GL_ELEMENT_ARRAY_BUFFER,
         PixelPack = GL_PIXEL_PACK_BUFFER,
         PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
         Texture = GL_TEXTURE_BUFFER,
         TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
         Uniform = GL_UNIFORM_BUFFER
      };

      Buffer() {
         glGenBuffers(1, &buffer_id_);
         DEBUG_M("Created buffer %d.", buffer_id_);
         logGLError();
         target_ = Array;
         usage_ = StaticDraw;
      }

      ~Buffer() {
         DEBUG_M("Deconstructing buffer %d.", buffer_id_);
         glDeleteBuffers(1, &buffer_id_);
         logGLError();
      }

      void setTarget(const Target target) {
         target_ = target;
      }

      void bind() {
         bind(target_);
         logGLError();
      }

      void bind(const Target target) {
         DEBUG_H("Binding buffer %d", buffer_id_);
         glBindBuffer(target, buffer_id_);
         target_ = target;
         logGLError();
      }
      
      void unbind() {
         glBindBuffer(target_, 0);
      }

      void data(const Target target, const GLsizei size, const void* data, const Usage usage=StaticDraw) {
         bufferData_(target, size, data, usage);
      }

      void data(const GLsizei size, const void* data, const Usage usage=StaticDraw) {
         bufferData_(target_, size, data, usage);
      }

      GLsizei getSize() const {
         return size_;
      }

   private:
      void bufferData_(const Target target, const GLsizei size, const void* data, const Usage usage=StaticDraw) {
         bind();
         size_ = size;
         target_ = target;
         usage_ = usage;
         glBufferData(target, size, data, usage);
         logGLError();
      }

      GLuint buffer_id_;
      Target target_;
      GLsizei size_;
      Usage usage_;
};

#endif /* G3_BUFFER_HPP_ */
