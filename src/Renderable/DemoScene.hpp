#ifndef G3TEST_DEMOSCENE_HPP_
#define G3TEST_DEMOSCENE_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "../OpenGL/GLMatrixStack.hpp"
#include "../OpenGL/Program.hpp"

class Cube;
class Framebuffer;
class Renderbuffer;
class Texture;
class ErrorMesh;

class DemoScene {
   public:
      DemoScene(const int width=800, const int height=600);
      void render();
      void setSize(const int width, const int height);
      void update(const float dt);

   private:
      void bindMatrices_();

      std::shared_ptr<Framebuffer> framebuffer_;
      std::shared_ptr<Renderbuffer> colorbuffer_;
      std::shared_ptr<Renderbuffer> depthbuffer_;
      std::shared_ptr<Texture> texture_;
      int width_;
      int height_;
      ProgramPtr program_;
      std::shared_ptr<Cube> cube_;
      std::shared_ptr<ErrorMesh> em_;
      float cube_rotation_;
      glm::mat4 projection_matrix_;
      GLMatrixStack stack_;
      GLint mvp_loc_;
      GLint mv_loc_;
      GLint nm_loc_;
};

#endif /* G3TEST_DEMOSCENE_HPP_ */
