#ifndef G3TEST_FRAMEBUFFER_HPP_
#define G3TEST_FRAMEBUFFER_HPP_

#include "OpenGL.hpp"
#include "Renderbuffer.hpp"

class Framebuffer {
   public:

      enum Target :GLenum {
         DrawFramebuffer = GL_DRAW_FRAMEBUFFER,
         ReadFramebuffer = GL_READ_FRAMEBUFFER,
         DefaultFramebuffer = GL_FRAMEBUFFER
      };

      static LookupNames AttachmentNames;
      static LookupNames TargetNames;
      static LookupNames StatusNames;

      enum AttachmentType :GLenum {
         Color = GL_COLOR_ATTACHMENT0,
         Color0 = GL_COLOR_ATTACHMENT0,
         Color1 = GL_COLOR_ATTACHMENT1,
         Color2 = GL_COLOR_ATTACHMENT2,
         Color3 = GL_COLOR_ATTACHMENT3,
         Depth = GL_DEPTH_ATTACHMENT,
         Stencil = GL_STENCIL_ATTACHMENT,
         DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT
      };

      Framebuffer();
      ~Framebuffer();
      void bind();
      static void unbind();
      void bind(const Target target);
      void renderbuffer(const RenderbufferPtr rb, const Target target, const AttachmentType attachment);
      void renderbuffer(const RenderbufferPtr rb, const AttachmentType attachment);
      GLenum checkStatus() const;
      GLuint getID() const;      
      Target getTarget() const;

   private:
      void setID_(const GLuint id);
      void setTarget(const Target target);

      GLuint id_;
      Target target_;
};

typedef std::shared_ptr<Framebuffer> FramebufferPtr;

inline void Framebuffer::bind() {
   bind(getTarget());
}

inline void Framebuffer::bind(const Target target) {
   setTarget(target);
   glBindFramebuffer(getTarget(), getID());
   logGLError();
}

inline void Framebuffer::unbind() {
   glBindFramebuffer(DrawFramebuffer, 0);
   logGLError();
   glBindFramebuffer(ReadFramebuffer, 0);
   logGLError();
}

#endif /* G3TEST_FRAMEBUFFER_HPP_ */

