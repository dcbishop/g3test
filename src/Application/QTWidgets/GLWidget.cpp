#include "GLWidget.hpp"

#include <iostream>
using namespace std;

#include "../../Renderable/DemoScene.hpp"

GLWidget::GLWidget(QWidget *parent) :
   QGLWidget(parent)
{
   connect(&update_timer_, SIGNAL(timeout()), this, SLOT(updateGL()));
}

void GLWidget::initializeGL() {

#ifdef USE_GLEW
   glewInit();
#endif

   demo_scene_ = shared_ptr<DemoScene>(new DemoScene());
   timer_.start();
   update_timer_.start(16);
}

void GLWidget::resizeGL(int w, int h) {
   demo_scene_->setSize(w, h);
   updateGL();
}

void GLWidget::paintGL() {
   demo_scene_->update(timer_.restart()/1000.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   demo_scene_->render();
   swapBuffers();
}

