#ifndef G3TEST_DEMOSCENE_HPP_
#define G3TEST_DEMOSCENE_HPP_

#include <glm/glm.hpp>

#include "../OpenGL/GLMatrixStack.hpp"

class Cube;

class DemoScene {
   public:
      DemoScene(const int width, const int height);
      void render();
      void setSize(const int width, const int height);

   private:
      Cube* cube_;
      glm::mat4 projection_matrix_;
      GLMatrixStack stack_;
      int width_;
      int height_;
};

#endif /* G3TEST_DEMOSCENE_HPP_ */
