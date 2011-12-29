#include "Widget.hpp"

#include <QtGui>
#include "GLWidget.hpp"

Widget::Widget() {
   resize(800, 600);
   setWindowTitle(QApplication::translate("qtapplication", "QT Application"));

   glwidget_ = new GLWidget(this);
   QHBoxLayout *layout = new QHBoxLayout();
   layout->addWidget(glwidget_);
   setLayout(layout);
   show();
}

void Widget::redraw() {
   glwidget_->updateGL();
}
