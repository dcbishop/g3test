#include "GLUTApplication.hpp"

#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#include <GL/freeglut.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "../Renderable/DemoScene.hpp"

#include "../Debug/console.h"

DemoScene* GLUTApplication::demo_scene_ = nullptr;

GLUTApplication::GLUTApplication(int& argc, char* argv[]) {
   glutInit(&argc, argv); 
   glutInitWindowSize(800, 600);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
   glutInitContextVersion(3, 3);
   glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
   /*glutInitContextProfile(GLUT_CORE_PROFILE);*/
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
   //glutIdleFunc(idle_);
   glutDisplayFunc(render_);
   glutReshapeFunc(resize_);
   glutCreateWindow("GLUT Application");
   glutTimerFunc(1000/60, timer_, 0);
   demo_scene_ = new DemoScene(800, 600);
}

GLUTApplication::~GLUTApplication() {
   delete demo_scene_;
}

void GLUTApplication::run() {
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glutMainLoop();
}

void GLUTApplication::setSize(const int width, const int height) {
   demo_scene_->setSize(width, height);
}

void GLUTApplication::update() {
   using namespace boost::posix_time;

   static ptime last(microsec_clock::local_time());

   static ptime current;
   current = microsec_clock::local_time();

   static time_duration diff;
   diff = current - last;

   GLUTApplication::demo_scene_->update(diff.total_milliseconds()/1000.0f);
   if(diff.total_milliseconds()/1000.0f != 0.0f) {
      last = current;
   }
}

void idle_(void) {
   // Do nothing...
}

void render_(void) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   GLUTApplication::demo_scene_->render();
   glutSwapBuffers();
}

void timer_(int) {
   GLUTApplication::update();
   render_();
   glutPostRedisplay();
   glutTimerFunc(1000/60, timer_, 0);
}

void resize_(int w, int h) {
   GLUTApplication::setSize(w, h);
   glutPostRedisplay();
}
