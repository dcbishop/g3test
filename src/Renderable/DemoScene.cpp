#include "DemoScene.hpp"
#include "Cube.hpp"

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

DemoScene::DemoScene(const int width, const int height) {
   cube_ = new Cube();
   setSize(width, height);
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClearDepth(10000.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DemoScene::render() {
   stack_.loadIdentity();
   glLoadMatrixf(stack_.getOpenGLMatrix());
   cube_->render();
}

void DemoScene::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
   projection_matrix_ = glm::perspective(90.0f, (float)1.0 * width_ / height_, 0.1f, 10000.0f);
}
