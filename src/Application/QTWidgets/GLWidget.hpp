#ifndef G3TEST_GLWIDGET_HPP_
#define G3TEST_GLWIDGET_HPP_

#include "../../OpenGL/OpenGL.hpp"

#include <QGLWidget>
#include <QTimer>
#include <QElapsedTimer>

#include <memory>
using std::shared_ptr;

#include "../../OpenGL/OpenGL.hpp"

class DemoScene;

class GLWidget : public QGLWidget {
   Q_OBJECT

   public:
      explicit GLWidget(QWidget *parent = 0);
      void initializeGL();
      void resizeGL(int w, int h);
      void paintGL();

   private:
      GLuint buff_id;
      GLuint vertex_attribute_id;
      GLuint vertex_shader_id;
      GLuint fragment_shader_id;
      GLuint shader_program_id;
      shared_ptr<DemoScene> demo_scene_;
      QElapsedTimer timer_;
      QTimer update_timer_;
      
};

#endif /* G3TEST_GLWIDGET_HPP_ */
