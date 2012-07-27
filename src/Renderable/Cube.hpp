#ifndef G3TEST_CUBE_HPP_
#define G3TEST_CUBE_HPP_

#include <glm/glm.hpp>
#include <dglw/dglw.hpp>

class Cube {
   public:
      Cube();
      ~Cube();
      void init();
      void deinit();
      void render();

   private:
      glm::vec3 position_;
      glm::vec4 rotation_;
      dglw::VertexArray array_;
      dglw::Buffer buffer_;
      static bool isInitilized_;
      static unsigned int refs_;
};

#endif /* G3TEST_CUBE_HPP_ */
