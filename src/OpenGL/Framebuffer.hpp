#ifndef G3TEST_FRAMEBUFFER_HPP_
#define G3TEST_FRAMEBUFFER_HPP_

#include "OpenGL.hpp"
#include "Renderbuffer.hpp"

class Framebuffer {
   public:

      enum FramebufferTarget :GLenum {
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


      Framebuffer() {
         setID_(0);
         setTarget(DrawFramebuffer);
         glGenFramebuffers(1, &id_);
      }

      ~Framebuffer() {
         glDeleteFramebuffers(1, &id_);
      }

      void bind() {
         bind(getTarget());
      }
      
      static void unbind() {
         glBindFramebuffer(DrawFramebuffer, 0);
         logGLError();
         glBindFramebuffer(ReadFramebuffer, 0);
         logGLError();
      }

      void bind(const FramebufferTarget target) {
         //DEBUG_M("Binding Framebuffer %d with target %s", getID(), TargetNames[target].c_str());
         setTarget(target);
         glBindFramebuffer(getTarget(), getID());
         logGLError();
      }

      void renderbuffer(const RenderbufferPtr rb, const FramebufferTarget target, const AttachmentType attachment) {
         DEBUG_M("Attaching Framebuffer %d (%s) with Renderbuffer %d (%s)", getID(), TargetNames[target].c_str(), rb->getID(), AttachmentNames[attachment].c_str());
         setTarget(target);
         //bind(getTarget());
         logGLError();
         glFramebufferRenderbuffer(getTarget(), attachment, GL_RENDERBUFFER, rb->getID());
         logGLError();
      }

      void renderbuffer(const RenderbufferPtr rb, const AttachmentType attachment) {
         renderbuffer(rb, getTarget(), attachment);
      }

      GLenum checkStatus() const {
         return glCheckFramebufferStatus(getTarget());
      }

      GLuint getID() const {
         return id_;
      }
      
      FramebufferTarget getTarget() const {
         return target_;
      }

   private:
      void setID_(const GLuint id) {
         id_ = id;
      }

      void setTarget(const FramebufferTarget target) {
         target_ = target;
      }

      GLuint id_;
      FramebufferTarget target_;
};
typedef shared_ptr<Framebuffer> FramebufferPtr;

#endif /* G3TEST_FRAMEBUFFER_HPP_ */

