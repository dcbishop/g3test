#include "DemoScene.hpp"

using namespace dglw;

#include <string>
using std::string;

#include "../Main/Globals.hpp"
#include "../Renderable/Cube.hpp"
#include "../Renderable/ErrorMesh.hpp"
#include "../Renderable/TextureQuad.hpp"
#include "../Main/ResourceManager.hpp"
#include <dglw/dglw.hpp>

#include "../Debug/console.h"

DemoScene::DemoScene(const int width, const int height) {
   using std::shared_ptr;

   ResourceManager& rm = globals.getResourceManager();
   sm_ = ShaderManagerPtr(new ShaderManager);
   em_ = shared_ptr<ErrorMesh>(new ErrorMesh());
   cube_ = shared_ptr<Cube>(new Cube());
   cube_rotation_ = 45.0f;
   tq_ = shared_ptr<TextureQuad>(new TextureQuad());
   tq_->setProgram(sm_->getProgram(ShaderManager::FlatTexture));

   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glEnable(GL_CULL_FACE);

   setSize(width, height);
}

void DemoScene::bindMatrices_() {
   static SharedUniforms ubo_ = sm_->getSharedUniforms();
   glm::mat4 mvp_matrix = projection_matrix_ * stack_.getMatrix();

   sm_->setUniform(SharedUniforms::MVPMatrix, mvp_matrix);
   sm_->setUniform(SharedUniforms::MVMatrix, stack_.getMatrix());
   sm_->setUniform(SharedUniforms::NormalMatrix, stack_.getNormalMatrix());
   sm_->setUniform(SharedUniforms::ProjectionMatrix, projection_matrix_);
}

void DemoScene::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;

   projection_matrix_ = glm::perspective(90.0f, (float)1.0 * width_ / height_, 0.1f, 10000.0f);
   projection_matrix_ *= glm::lookAt(
      glm::vec3(0.0f, 0.0f, 2.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f));
   sm_->setUniform(SharedUniforms::ViewPort, glm::ortho(0.0f, (float)width_, 0.0f, (float)height_, 0.1f, 10000.0f));
   bindMatrices_();

   colorbuffer_ = dglw::RenderbufferPtr(new Renderbuffer);
   colorbuffer_->bind();
   colorbuffer_->storage(dglw::RGBA, width_, height_);

   logGLError();

   depthbuffer_ = RenderbufferPtr(new Renderbuffer);
   depthbuffer_->bind();
   depthbuffer_->storage(dglw::DepthComponnt24, width_, height_);

   logGLError();

   texture_.push_back(TexturePtr(new Texture));
   glActiveTexture(GL_TEXTURE0);
   texture_[0]->bind(Texture::Texture2D);
   texture_[0]->image2D(Texture::Texture2D, 0, dglw::RGBA, width_, height_,
                     0, Texture::RGBA, Texture::UnsignedByte, nullptr);
   texture_[0]->setMinFilter(Texture::Linear);
   texture_[0]->setMagFilter(Texture::Linear);

   texture_.push_back(TexturePtr(new Texture));
   glActiveTexture(GL_TEXTURE1);
   texture_[1]->bind(Texture::Texture2D);
   texture_[1]->image2D(Texture::Texture2D, 0, dglw::RGBA, width_, height_,
                     0, Texture::RGBA, Texture::UnsignedByte, nullptr);
   texture_[1]->setMinFilter(Texture::Linear);
   texture_[1]->setMagFilter(Texture::Linear);

   framebuffer_ = FramebufferPtr(new Framebuffer);
   framebuffer_->bind();
   framebuffer_->texture(texture_[0], Framebuffer::Color);
   framebuffer_->texture(texture_[1], Framebuffer::Color1);
   framebuffer_->renderbuffer(depthbuffer_, Framebuffer::Depth);
   logGLError();

   DEBUG_M("Framebuffer Status: %s", Framebuffer::StatusNames[framebuffer_->checkStatus()].c_str());

   glEnable(GL_DEPTH_TEST);
   logGLError();
   framebuffer_->unbind();
   glViewport(0, 0, width_, height_);
   sm_->setUniform(SharedUniforms::Resolution, glm::vec2(width, height));
   logGLError();
}

void DemoScene::update(const float dt) {
   static float rotate_speed = 45.0f;
   cube_rotation_ += rotate_speed * dt;
   if(cube_rotation_ > 360.0f) {
      cube_rotation_ -= 360.0f;
   }

   globals.setGametime(globals.getGametime()+dt);
   sm_->setUniform(SharedUniforms::Time, globals.getGametime());
}

void DemoScene::render() {
   stack_.loadIdentity();
   stack_.pushMatrix();
   stack_.rotate(cube_rotation_, 0.0f, 1.0f, 0.0f);
   bindMatrices_();

   static GLfloat red = 0.0f;
   red+=0.025;
   if(red>1.0f) {
      red=0.0f;
   }

   logGLError();
   framebuffer_->bind(Framebuffer::DrawFramebuffer);
   logGLError();

   static std::vector<GLenum> drawBufs = { Framebuffer::Color, Framebuffer::Color1 };
   glDrawBuffers(drawBufs.size(), &drawBufs[0]);

   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //cube_->render();
   em_->render();
   stack_.popMatrix();

   framebuffer_->unbind();
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   tq_->render();

   //framebuffer_->bind(Framebuffer::ReadFramebuffer);
   logGLError();

   //glBlitFramebuffer( 0, 0, width_, height_, 0, 0, width_, height_, GL_COLOR_BUFFER_BIT, GL_NEAREST );
   logGLError();
   framebuffer_->unbind();
}
