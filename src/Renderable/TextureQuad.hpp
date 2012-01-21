#ifndef G3TEST_TEXTUREQUAD_HPP_
#define G3TEST_TEXTUREQUAD_HPP_

#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/VertexArray.hpp"
#include "../OpenGL/Buffer.hpp"
#include "../OpenGL/Program.hpp"

class TextureQuad {
   public:
      TextureQuad();
      ~TextureQuad();
      void render();
      void setProgram(const ProgramPtr& program);

   private:
      void init_();
      void deinit_();

      static unsigned int refs_;
      static bool isInitilized_;

      static VertexArrayPtr array_;
      static BufferPtr buffer_;
      ProgramPtr program_;
      GLuint texture_loc_;
      GLuint time_loc_;
};

#endif /* G3TEST_TEXTUREQUAD_HPP_ */
