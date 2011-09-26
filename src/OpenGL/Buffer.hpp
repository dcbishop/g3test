#ifndef G3_BUFFER_HPP_
#define G3_BUFFER_HPP_

#include <GL3/gl3.h>

class Buffer {
   public:
      Buffer() {
   		glGenBuffers(1, &buffer_);
   	}

   	~Buffer() {
   	   glDeleteBuffers(1, &buffer_);
      }

   private:
      GLuint buffer_;
};

#endif /* G3_BUFFER_HPP_ */
