#include "Buffer.hpp"

Buffer::Buffer() {
   glGenBuffers(1, &buffer_id_);
   DEBUG_M("Created buffer %d.", buffer_id_);
   logGLError();
   target_ = Array;
   usage_ = StaticDraw;
}

Buffer::~Buffer() {
   DEBUG_M("Deconstructing buffer %d.", buffer_id_);
   glDeleteBuffers(1, &buffer_id_);
   logGLError();
}

void Buffer::setTarget(const Target target) {
   target_ = target;
}
