#include "DemoScene.hpp"

#include <string>
using std::string;

#include "../Renderable/Cube.hpp"
#include "../Renderable/ErrorMesh.hpp"
#include "../Main/Filesystem.hpp"
#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Shader.hpp"
#include "../OpenGL/Framebuffer.hpp"
#include "../OpenGL/Renderbuffer.hpp"


#include "../Debug/console.h"

DemoScene::DemoScene(const int width, const int height) {
   using namespace ResourceManager;
   using std::shared_ptr;

   em_ = shared_ptr<ErrorMesh>(new ErrorMesh());
   //cube_ = shared_ptr<Cube>(new Cube());
   cube_rotation_ = 45.0f;

   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glEnable(GL_CULL_FACE);

   // Load the vertex shader
   auto vertex_source = readIntoVector(findShaderFile("Basic.vert"));
   static Shader vertex_shader(Shader::Vertex, vertex_source);
   vertex_shader.compile();
   logGLError();
   vertex_shader.debugLog();

   // Load the fragment shader
   auto fragment_source = readIntoVector(findShaderFile("Basic.frag"));
   static Shader fragment_shader(Shader::Fragment, fragment_source);
   fragment_shader.compile();
   logGLError();
   vertex_shader.debugLog();

   // Make a shader program
   program_.attach(vertex_shader);
   program_.attach(fragment_shader);
   
   // Bind shader program attributes
   /*program_.bindAttribLocation(AttributeIndex::Vertex, AttributeName::Vertex);
   program_.bindAttribLocation(AttributeIndex::Normal, AttributeName::Normal);
   program_.bindAttribLocation(AttributeIndex::Color, AttributeName::Color);*/
   logGLError();

   program_.link();
   logGLError();
   program_.use();
   logGLError();

   // Bind shader program uniform attributes
   mv_loc_ = program_.getUniformLocation(UniformName::ModelViewMatrix);
   logGLError();
   mvp_loc_ = program_.getUniformLocation(UniformName::ModelViewProjectionMatrix);
   logGLError();
   nm_loc_ = program_.getUniformLocation(UniformName::NormalMatrix);
   logGLError();
   setSize(width, height);
}

void DemoScene::bindMatrices_() {
   program_.use();
   glm::mat4 mvp_matrix = projection_matrix_ * stack_.getMatrix();
   program_.uniformMatrix(mvp_matrix, mvp_loc_);
   program_.uniformMatrix(stack_.getMatrix(), mv_loc_);
   program_.uniformMatrix(stack_.getNormalMatrix(), nm_loc_);
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
   colorbuffer_->storage(Renderbuffer::RGBA, width_, height_);

   logGLError();

   depthbuffer_ = RenderbufferPtr(new Renderbuffer);
   depthbuffer_->bind();
   depthbuffer_->storage(Renderbuffer::DepthComponnt24, width_, height_);

   logGLError();

   framebuffer_ = FramebufferPtr(new Framebuffer);
   logGLError();
   framebuffer_->bind();
   logGLError();
   framebuffer_->renderbuffer(colorbuffer_, Framebuffer::Color);
   logGLError();
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
