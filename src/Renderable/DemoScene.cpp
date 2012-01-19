#include "DemoScene.hpp"

#include <string>
using std::string;

#include "../Main/Globals.hpp"
#include "../Renderable/Cube.hpp"
#include "../Renderable/ErrorMesh.hpp"
#include "../Main/ResourceManager.hpp"
#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Shader.hpp"
#include "../OpenGL/Framebuffer.hpp"
#include "../OpenGL/Renderbuffer.hpp"
#include "../OpenGL/Texture.hpp"

#include "../Debug/console.h"

DemoScene::DemoScene(const int width, const int height) {
   using std::shared_ptr;

   ResourceManager& rm = globals.getResourceManager();

   em_ = shared_ptr<ErrorMesh>(new ErrorMesh());
   //cube_ = shared_ptr<Cube>(new Cube());
   cube_rotation_ = 45.0f;

   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glEnable(GL_CULL_FACE);

   // Load the vertex/fragment shader.
   program_ = rm.getVFProgram("Basic.vert", "Basic.frag");
   program_->debugLog();
      logGLError();
   program_->use();
   logGLError();

   // Bind shader program uniform attributes
   mv_loc_ = program_->getUniformLocation(UniformName::ModelViewMatrix);
   logGLError();
   mvp_loc_ = program_->getUniformLocation(UniformName::ModelViewProjectionMatrix);
   logGLError();
   nm_loc_ = program_->getUniformLocation(UniformName::NormalMatrix);
   logGLError();
   setSize(width, height);
}

void DemoScene::bindMatrices_() {
   program_->use();
   glm::mat4 mvp_matrix = projection_matrix_ * stack_.getMatrix();
   program_->uniformMatrix(mvp_matrix, mvp_loc_);
   program_->uniformMatrix(stack_.getMatrix(), mv_loc_);
   program_->uniformMatrix(stack_.getNormalMatrix(), nm_loc_);
}

void DemoScene::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;

   projection_matrix_ = glm::perspective(90.0f, (float)1.0 * width_ / height_, 0.1f, 10000.0f);
   projection_matrix_ *= glm::lookAt(
      glm::vec3(0.0f, 0.0f, 2.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f));
   bindMatrices_();

   logGLError();

   colorbuffer_ = RenderbufferPtr(new Renderbuffer);
   colorbuffer_->bind();
   colorbuffer_->storage(g3::RGBA, width_, height_);

   logGLError();

   depthbuffer_ = RenderbufferPtr(new Renderbuffer);
   depthbuffer_->bind();
   depthbuffer_->storage(g3::DepthComponnt24, width_, height_);

   logGLError();

   texture_ = TexturePtr(new Texture);
   glActiveTexture(GL_TEXTURE0);
   texture_->bind(Texture::Texture2D);
   texture_->image2D(Texture::Texture2D, 0, g3::RGBA, width_, height_,
                     0, Texture::RGBA, Texture::UnsignedByte, nullptr);
   texture_->setMinFilter(Texture::Linear);
   texture_->setMagFilter(Texture::Linear);

   framebuffer_ = FramebufferPtr(new Framebuffer);
   framebuffer_->bind();
   framebuffer_->texture(texture_, Framebuffer::Color);
   framebuffer_->renderbuffer(depthbuffer_, Framebuffer::Depth);
   logGLError();

   LOG("Framebuffer Status: %s", Framebuffer::StatusNames[framebuffer_->checkStatus()].c_str());

   glEnable(GL_DEPTH_TEST);
   logGLError();
   framebuffer_->unbind();
   glViewport(0, 0, width_, height_);
   logGLError();
}

void DemoScene::update(const float dt) {
   static float rotate_speed = 45.0f;
   cube_rotation_ += rotate_speed * dt;
   if(cube_rotation_ > 360.0f) {
      cube_rotation_ -= 360.0f;
   }
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
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   static std::vector<GLenum> drawBufs = { Framebuffer::Color };
   glDrawBuffers(drawBufs.size(), &drawBufs[0]);

   //cube_->render();
   em_->render();
   stack_.popMatrix();
   framebuffer_->unbind();
   logGLError();
   framebuffer_->bind(Framebuffer::ReadFramebuffer);
   logGLError();

   glBlitFramebuffer( 0, 0, width_, height_, 0, 0, width_, height_, GL_COLOR_BUFFER_BIT, GL_NEAREST );
   logGLError();
   framebuffer_->unbind();
}
