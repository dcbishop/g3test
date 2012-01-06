#include <iostream>
using namespace std;

#include "Globals.hpp"
#include "../Debug/console.h"

#include "../Application/GLFWApplication.hpp"
#include "../Application/GLUTApplication.hpp"
#include "../Application/SFMLApplication.hpp"
#include "../Application/QTApplication.hpp"

int main(int argc, char* argv[]) {
   LOG("Starting %s %s, built: %s...", argv[0], globals.getGitVersion().c_str(), globals.getBuildDate().c_str());

   /*GLUTApplication app(argc, argv);
   app.run();*/
   /*SFMLApplication app;
   app.run();*/
   /*GLFWApplication app;
   app.run();*/
   QTApplication app(argc, argv);
   app.run();

   LOG("Finished...");
}
