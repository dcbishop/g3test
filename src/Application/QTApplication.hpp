#ifndef G3TEST_QTAPPLICATION_HPP_
#define G3TEST_QTAPPLICATION_HPP_

#include <QtGui>

#include <memory>
using std::shared_ptr;

class Widget;

typedef shared_ptr<QApplication> QAppPtr;

class QTApplication {
   public:
      QTApplication(int argc, char **argv);
      ~QTApplication();

      void setSize(const int width, const int height);
      void run();

   private:
      shared_ptr<QApplication> qapp_;
      shared_ptr<Widget> widget_;
      int width_;
      int height_;
};

#endif /* G3TEST_QTAPPLICATION_HPP_ */
