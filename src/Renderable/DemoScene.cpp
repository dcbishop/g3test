#include "DemoScene.hpp"
#include "Cube.hpp"

#include <string>
using std::string;

#include "../Main/Filesystem.hpp"
#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Shader.hpp"

#include "../Debug/console.h"

DemoScene::DemoScene(const int width, const int height) {
   cube_ = new Cube();
   cube_rotation_ = 45.0f;

   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_CULL_FACE);
   
   // Load the vertex shader
   string vertex_filename = findShaderFile("Basic.vert");
   auto vertex_source = readIntoVector(vertex_filename);
   static Shader vertex_shader(Shader::Vertex, vertex_source);
   vertex_shader.compile();
   logGLError();
   vertex_shader.debugLog();

   // Load the fragment shader
   string fragment_filename = findShaderFile("Basic.frag");
   auto fragment_source = readIntoVector(fragment_filename);
   static Shader fragment_shader(Shader::Fragment, fragment_source);
   fragment_shader.compile();
   logGLError();
   vertex_shader.debugLog();

   // Make a shader program
   program_.attach(vertex_shader);
   program_.attach(fragment_shader);
   
   // Bind shader program attributes
   program_.bindAttribLocation(AttributeIndex::Vertex, AttributeName::Vertex);
   program_.bindAttribLocation(AttributeIndex::Normal, AttributeName::Normal);
   program_.bindAttribLocation(AttributeIndex::Color, AttributeName::Color);
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

void DemoScene::render() {
   stack_.loadIdentity();
   stack_.pushMatrix();
   stack_.rotate(cube_rotation_, 0.0f, 1.0f, 0.0f);
   bindMatrices_();
   cube_->render();
   stack_.popMatrix();
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
}

void DemoScene::update(const float dt) {
   static float rotate_speed = 45.0f;
   cube_rotation_ += rotate_speed * dt;
   if(cube_rotation_ > 360.0f) {
      cube_rotation_ -= 360.0f;
   }
}
