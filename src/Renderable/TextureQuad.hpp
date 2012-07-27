#ifndef G3TEST_TEXTUREQUAD_HPP_
#define G3TEST_TEXTUREQUAD_HPP_

#include <dglw/dglw.hpp>

class TextureQuad {
   public:
      TextureQuad();
      ~TextureQuad();
      void render();
      void setProgram(const dglw::ProgramPtr& program);

   private:
      void init_();
      void deinit_();

      static unsigned int refs_;
      static bool isInitilized_;

      static dglw::VertexArrayPtr array_;
      static dglw::BufferPtr buffer_;
      dglw::ProgramPtr program_;
      GLuint texture_loc_;
      GLuint time_loc_;
};

#endif /* G3TEST_TEXTUREQUAD_HPP_ */
