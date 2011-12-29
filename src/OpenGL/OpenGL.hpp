#ifndef G3TEST_OPENGL_HPP_
#define G3TEST_OPENGL_HPP_

#include <string>
#include <vector>

#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#include <GL/freeglut.h>

#include "../Debug/console.h"

#ifdef _DEBUG
#define logGLError() for(long err = glGetError(); err; err = glGetError()) { ERROR("OpenGL: %s", (char*)gluErrorString(err)); }
#else
#define logGLError()
#endif /* _DEBUG */

namespace AttributeIndex {
   enum AttributeIndex {
      Vertex = 0,
      Normal = 2,
      Color = 3,
      SecondaryColor = 4,
      FogCoord = 5,
      MultiTextCoord0 = 8,
      MultiTextCoord1 = 9,
      MultiTextCoord2 = 10,
      MultiTextCoord3 = 11,
      MultiTextCoord4 = 12,
      MultiTextCoord5 = 13,
      MultiTextCoord6 = 14,
      MultiTextCoord7 = 15
   };
}

namespace AttributeName {
   static const GLchar* Vertex = "Position";
   static const GLchar* Position = "Position";
   static const GLchar* Normal = "Normal";
   static const GLchar* Color = "Color";
}

namespace UniformName {
   static const GLchar* ModelViewMatrix = "MVMatrix";
   static const GLchar* ModelViewProjectionMatrix = "MVPMatrix";
   static const GLchar* NormalMatrix = "NormalMatrix";
}
#endif /* G3TEST_OPENGL_HPP_ */
