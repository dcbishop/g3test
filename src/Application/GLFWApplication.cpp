#include "GLFWApplication.hpp"

#include "../OpenGL/OpenGL.hpp"
#include <GL/glfw.h>
#include "../Renderable/DemoScene.hpp"

#include "../Debug/console.h"

GLFWApplication::GLFWApplication() {
   if(!glfwInit()) {
      ERROR("Failed to initilize GLFW.");
      return;
   }

}

GLFWApplication::~GLFWApplication() {
   glfwTerminate();
}

void GLFWApplication::setSize(const int width, const int height) {
   glfwSetWindowSize(width, height);
   demo_scene_->setSize(width, height);
   width_ = width;
   height_ = height;
}


void GLFWApplication::run() {
   bool running = true;

   if(!glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
      ERROR("Could now open GLFW window.");
      glfwTerminate();
      return;
   }
   glfwSetWindowTitle("GLFW Application");
   
#ifdef USE_GLEW
   glewInit();
#endif

   demo_scene_ = new DemoScene();
   setSize(800, 600);
   while(running) {
      update();
      render();
   }
}

void GLFWApplication::update() {
   static double last = glfwGetTime();

   static double current;
   current = glfwGetTime();

   static double diff;
   diff = current - last;

   demo_scene_->update(diff);
   if(glfwGetTime() != 0.0) {
      last = current;
   }
}

void GLFWApplication::render() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   demo_scene_->render();
   glfwSwapBuffers();
}
