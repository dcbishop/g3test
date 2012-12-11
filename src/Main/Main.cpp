#include <iostream>
using namespace std;

#include "Globals.hpp"
#include "../Debug/console.h"

#ifdef USE_QT
#include "../Application/QTApplication.hpp"
#endif

#ifdef USE_SFML
#include "../Application/SFMLApplication.hpp"
#endif

#ifdef USE_GLFW
#include "../Application/GLFWApplication.hpp"
#endif

#ifdef USE_GLUT
#include "../Application/GLUTApplication.hpp"
#endif

int main(int argc, char* argv[]) {
   LOG("Starting %s %s %s, built: %s...",
      argv[0],
      globals.getGitVersion().c_str(),
      globals.getBuildType().c_str(),
      globals.getBuildDate().c_str()
   );

   // [TODO]: Remove the use of internal Application and use the dglw ones.
   //         Requires moving demo_scene out of the applications.

#ifdef USE_QT
   QTApplication app(argc, argv);
   app.run();
#endif

#ifdef USE_SFML
   SFMLApplication app;
   app.run();
#endif
   
#ifdef USE_GLFW
   GLFWApplication app;
   app.run();
#endif

#ifdef USE_GLUT
   GLUTApplication app(argc, argv);
   app.run();
#endif

   dglw::initialize(); 
  
   LOG("Finished...");
}
