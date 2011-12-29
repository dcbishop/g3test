#include "QTApplication.hpp"

#include "QTWidgets/Widget.hpp"

QTApplication::QTApplication(int argc, char *argv[]) {
   qapp_ = shared_ptr<QApplication>(new QApplication(argc, argv));
}

QTApplication::~QTApplication() {

}

void QTApplication::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;
}

void QTApplication::run() {
   widget_ = shared_ptr<Widget>(new Widget);
   qapp_->exec();
}
