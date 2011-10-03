#include <iostream>
using namespace std;

#include "Globals.hpp"
#include "../Debug/console.h"

#include "GLFWApplication.hpp"
#include "GLUTApplication.hpp"
#include "SFMLApplication.hpp"

int main(int argc, char* argv[]) {
   LOG("Starting %s %s, built: %s...", argv[0], g.getGitVersion().c_str(), g.getBuildDate().c_str());

   /*GLUTApplication app(argc, argv);
   app.run();*/
   /*SFMLApplication app;
   app.run();*/
   GLFWApplication app;
   app.run();

   LOG("Finished...");
}
