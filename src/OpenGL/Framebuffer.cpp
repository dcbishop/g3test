#include "Framebuffer.hpp"

// C++11 Only: Some uniform initlilization :)
LookupNames Framebuffer::AttachmentNames = {
   {GL_COLOR_ATTACHMENT0, "GL_COLOR_ATTACHMENT0"},
   {GL_COLOR_ATTACHMENT1, "GL_COLOR_ATTACHMENT1"},
   {GL_COLOR_ATTACHMENT2, "GL_COLOR_ATTACHMENT2"},
   {GL_COLOR_ATTACHMENT3, "GL_COLOR_ATTACHMENT3"},
   {GL_DEPTH_ATTACHMENT, "GL_DEPTH_ATTACHMENT"},
   {GL_STENCIL_ATTACHMENT, "GL_STENCIL_ATTACHMENT"},
   {GL_DEPTH_STENCIL_ATTACHMENT, "GL_DEPTH_STENCIL_ATTACHMENT"},
};

LookupNames Framebuffer::TargetNames = {
   {GL_FRAMEBUFFER, "GL_FRAMEBUFFER"}, 
   {GL_DRAW_FRAMEBUFFER, "GL_DRAW_FRAMEBUFFER"},
   {GL_READ_FRAMEBUFFER, "GL_READ_FRAMEBUFFER"}
};

LookupNames Framebuffer::StatusNames = {
   { GL_FRAMEBUFFER_COMPLETE, "GL_FRAMEBUFFER_COMPLETE" },
   { GL_FRAMEBUFFER_UNDEFINED, "GL_FRAMEBUFFER_UNDEFINED" },
   { GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" },
   { GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" },
   { GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" },
   { GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" },
   { GL_FRAMEBUFFER_UNSUPPORTED, "GL_FRAMEBUFFER_UNSUPPORTED" },
   { GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" }
};


Framebuffer::Framebuffer() {
   setID_(0);
   setTarget(DrawFramebuffer);
   glGenFramebuffers(1, &id_);
}

Framebuffer::~Framebuffer() {
   glDeleteFramebuffers(1, &id_);
}

void Framebuffer::renderbuffer(const RenderbufferPtr rb, const Target target, const AttachmentType attachment) {
   DEBUG_M("Attaching Framebuffer %d (%s) with Renderbuffer %d (%s)", getID(), TargetNames[target].c_str(), rb->getID(), AttachmentNames[attachment].c_str());
   setTarget(target);
   logGLError();
   glFramebufferRenderbuffer(getTarget(), attachment, GL_RENDERBUFFER, rb->getID());
   logGLError();
}

void Framebuffer::renderbuffer(const RenderbufferPtr rb, const AttachmentType attachment) {
   renderbuffer(rb, getTarget(), attachment);
}

GLenum Framebuffer::checkStatus() const {
   return glCheckFramebufferStatus(getTarget());
}

GLuint Framebuffer::getID() const {
   return id_;
}

Framebuffer::Target Framebuffer::getTarget() const {
   return target_;
}

void Framebuffer::setID_(const GLuint id) {
   id_ = id;
}

void Framebuffer::setTarget(const Target target) {
   target_ = target;
}
