#ifndef G3TEST_RENDERBUFFER_HPP_
#define G3TEST_RENDERBUFFER_HPP_

#include "OpenGL.hpp"

#include <memory>

class Renderbuffer {
   public:
      static LookupNames FormatNames;

      enum InternalFormat :GLenum {
         RGB = GL_RGB,
         RGBA = GL_RGBA,
         DepthComponnt = GL_DEPTH_COMPONENT,
         DepthComponnt16 = GL_DEPTH_COMPONENT16,
         DepthComponnt24 = GL_DEPTH_COMPONENT24,
         DepthComponnt32 = GL_DEPTH_COMPONENT32,
         DepthComponnt32F = GL_DEPTH_COMPONENT32F,
         StencilIndex = GL_STENCIL_INDEX
      };

      Renderbuffer() {
         id_ = 0;
         glGenRenderbuffers(1, &id_);
         logGLError();
         DEBUG_M("Generated renderbuffer %d", id_);
      }

      ~Renderbuffer() {
         glDeleteRenderbuffers(1, &id_);
         logGLError();
         DEBUG_M("Deleted renderbuffer %d", id_);
      }

      void bind() {
         glBindRenderbuffer(GL_RENDERBUFFER, id_);
         logGLError();
      }

      void storage(const InternalFormat internalformat, const GLsizei width, const GLsizei height) {
         bind();
         DEBUG_M("storage(%s, %d, %d)", FormatNames[internalformat].c_str(), width, height);
         glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
         logGLError();
      }

      void storageMultisample(const GLsizei samples, const InternalFormat internalformat, const GLsizei width, const GLsizei height) {
         bind();
         glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
         logGLError();
      }
      
      GLuint getID() const {
         return id_;
      }

   private:
      GLuint id_;
};
typedef std::shared_ptr<Renderbuffer> RenderbufferPtr;

#endif /* G3TEST_RENDERBUFFER_HPP_ */

