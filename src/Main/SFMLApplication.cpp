#include "SFMLApplication.hpp"

#include "../OpenGL/OpenGL.hpp"

#include "../Renderable/DemoScene.hpp"

#include "Filesystem.hpp"

SFMLApplication::SFMLApplication() {
   LOG("Constructing SFML Application...");

   window_ = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Window");
   window_->EnableVerticalSync(true);

   LOG("SFML v%d.%d, using OpenGL v%d.%d", SFML_VERSION_MAJOR, SFML_VERSION_MINOR, window_->GetSettings().MajorVersion, window_->GetSettings().MinorVersion);

   demo_scene_ = new DemoScene();
}

SFMLApplication::~SFMLApplication() {
   delete(demo_scene_);
}

void SFMLApplication::run() {
   LOG("Entering main loop...");

   sf::Clock clock;
   
   isRunning_ = true;
   while(isRunning_) {
      processEvents_();
      demo_scene_->update(clock.GetElapsedTime()/1000.0f);
      clock.Reset();
      render_();
   }

   LOG("Exiting main loop...");
}

void SFMLApplication::processEvents_() {
   sf::Event Event;

   while(window_->PollEvent(Event)) {
      // Window closed
      if(Event.Type == sf::Event::Closed) {
         isRunning_ = false;
      }

      // Escape key pressed
      if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Keyboard::Escape)) {
         isRunning_ = false;
      }
   }
}

void SFMLApplication::render_() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   demo_scene_->render();
   window_->Display();
}
