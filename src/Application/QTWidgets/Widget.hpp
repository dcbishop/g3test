#ifndef G3TEST_RAWQAPPLICATION_HPP_
#define G3TEST_RAWQAPPLICATION_HPP_

#include <QWidget>
#include <memory>
using std::shared_ptr;

class GLWidget;

class Widget : public QWidget {
   public:
      Widget();
      void redraw();

   private:
      GLWidget* glwidget_;
};

#endif /* G3TEST_RAWQAPPLICATION_HPP_ */

