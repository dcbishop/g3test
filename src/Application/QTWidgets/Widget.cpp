#include "Widget.hpp"

#include <QtGui>
#include "GLWidget.hpp"

Widget::Widget() {
   resize(800, 600);
   setWindowTitle(QApplication::translate("qtapplication", "QT Application"));

   // Setup the menu
   QMenuBar* menu_bar = new QMenuBar(this);

   QMenu* menu_file = new QMenu(menu_bar);
   menu_file->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));

   QAction* action_exit = new QAction(this);
   action_exit->setText(QApplication::translate("qtapplication", "E&xit", 0, QApplication::UnicodeUTF8));
   action_exit->setShortcut(tr("CTRL+X"));
   menu_bar->addSeparator();
   menu_bar->addAction(menu_file->menuAction());

   menu_file->addAction(action_exit);

   connect(action_exit, SIGNAL(triggered()), qApp, SLOT(quit()));
   setMenuBar(menu_bar);

   // Setup the GL widget
   glwidget_ = new GLWidget(this);
   glwidget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   QHBoxLayout *layout = new QHBoxLayout();
   layout->addWidget(glwidget_);

   // Put main GL widget into a frame
   QFrame* frame = new QFrame();
   frame->setFrameShape(QFrame::StyledPanel);
   frame->setLayout(layout);
   setCentralWidget(frame);

   // Setup the default docks
   /*QDockWidget* treedock1 = addTreeDock_();
   QDockWidget* treedock2 = addTreeDock_();
   this->addDockWidget(Qt::RightDockWidgetArea, treedock1);
   this->addDockWidget(Qt::LeftDockWidgetArea, treedock2);*/

   show();
}

void Widget::redraw() {
   glwidget_->updateGL();
}

QDockWidget* Widget::addTreeDock_() {
   QDockWidget* treedock = new QDockWidget(this);
   treedock->setFeatures(QDockWidget::AllDockWidgetFeatures);
   QTreeView* treeview = new QTreeView(this);
   treedock->setWidget(treeview);
   return treedock;
}
