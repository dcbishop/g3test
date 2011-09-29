#include "DemoScene.hpp"
#include "Cube.hpp"

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

#include "../Debug/console.h"

DemoScene::DemoScene(const int width, const int height) {
   cube_ = new Cube();
   cube_rotation_ = 45.0f;
   setSize(width, height);
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_CULL_FACE);
}

void DemoScene::render() {
   stack_.loadIdentity();
   stack_.pushMatrix();
   stack_.rotate(cube_rotation_, 0.0f, -1.0f, 0.0f);
   glm::mat4 temp = projection_matrix_ * stack_.getMatrix();
   glLoadMatrixf(&temp[0][0]);
   cube_->render();
   stack_.popMatrix();
}

void DemoScene::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
   projection_matrix_ = glm::perspective(90.0f, (float)1.0 * width_ / height_, 0.1f, 10000.0f);
   projection_matrix_ *= glm::lookAt(
      glm::vec3(0.0f, 0.0f, 2.0f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f));
}

void DemoScene::update(const float dt) {
   static float rotate_speed = 45.0f;
   cube_rotation_ += rotate_speed * dt;
   if(cube_rotation_ > 360.0f) {
      cube_rotation_ -= 360.0f;
   }
}
