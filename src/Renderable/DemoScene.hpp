#ifndef G3TEST_DEMOSCENE_HPP_
#define G3TEST_DEMOSCENE_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "../ShaderBinding/ShaderManager.hpp"

//class Cube;
/*class dglw::Framebuffer;
class dglw::Renderbuffer;
class dglw::Texture;*/
class ErrorMesh;
//class TextureQuad;

#include <dglw/dglw.hpp>

class DemoScene {
   public:
      DemoScene(const int width=800, const int height=600);
      void render();
      void setSize(const int width, const int height);
      void update(const float dt);

   private:
      void bindMatrices_();

      std::shared_ptr<dglw::Framebuffer> framebuffer_;
      std::shared_ptr<dglw::Renderbuffer> colorbuffer_;
      std::shared_ptr<dglw::Renderbuffer> depthbuffer_;
      std::vector<std::shared_ptr<dglw::Texture>> texture_;
      int width_;
      int height_;
      std::shared_ptr<dglw::Cube> cube_;
      std::shared_ptr<ErrorMesh> em_;
      std::shared_ptr<dglw::TextureQuad> tq_;
      float cube_rotation_;
      glm::mat4 projection_matrix_;
      dglw::MatrixStack stack_;
      ShaderManagerPtr sm_;
};

#endif /* G3TEST_DEMOSCENE_HPP_ */
