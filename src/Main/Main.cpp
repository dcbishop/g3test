#include <iostream>
using namespace std;

#include "Globals.hpp"
#include "../Debug/console.h"

#include "Application.hpp"

int main(int argc, char* argv[]) {
   LOG("Starting %s %s, build: %s...", argv[0], g.getGitVersion().c_str(), g.getBuildDate().c_str());

   Application app;
   app.run();

   LOG("Finished...");
}
