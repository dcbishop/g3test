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

   private:
      void init_();
      void deinit_();

      static unsigned int refs_;
      static bool isInitilized_;

      static VertexArrayPtr array_;
      static BufferPtr buffer_;
      static ProgramPtr program_;
};

#endif /* G3TEST_TEXTUREQUAD_HPP_ */
