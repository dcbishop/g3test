#ifndef G3TEST_RAWQAPPLICATION_HPP_
#define G3TEST_RAWQAPPLICATION_HPP_

#include <QMainWindow>
#include <QWidget>

#include <memory>
using std::shared_ptr;

class GLWidget;
class QDockWidget;

class Widget : public QMainWindow {
   public:
      Widget();
      void redraw();

   private:
      QDockWidget* addTreeDock_();

      GLWidget* glwidget_;
};

#endif /* G3TEST_RAWQAPPLICATION_HPP_ */

