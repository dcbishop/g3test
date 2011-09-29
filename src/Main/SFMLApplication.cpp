#include "Application.hpp"

#include <GL3/gl3.h>

#include "Filesystem.hpp"

Application::Application() {
   LOG("Constructing SFML Application...");

   window_ = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML Window");
   window_->EnableVerticalSync(true);

   /*const GLubyte* gl_version = glGetString(GL_VERSION);
   LOG("OpenGL version: \"%s\".", gl_version);*/
   LOG("SFML OpenGL version: %d.%d", window_->GetSettings().MajorVersion, window_->GetSettings().MinorVersion);
}

void Application::run() {
   LOG("Entering main loop...");

   sf::Texture texture;
   if(!texture.LoadFromFile(findImageFile("Stone_Bricks_01.png"))) {
      // 
   }

   sprite_.Move(32, 32);
   sprite_.SetTexture(texture);

   isRunning_ = true;
   while(isRunning_) {
      processEvents_();
      render_();
   }

   LOG("Exiting main loop...");
}

void Application::processEvents_() {
   sf::Event Event;
   /*while(window_->GetEvent(Event)) {
      // Window closed
      if(Event.Type == sf::Event::Closed) {
         isRunning_ = false;
      }

      // Escape key pressed
      if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) {
         isRunning_ = false;
      }
   }*/
}

void Application::render_() {
   window_->Clear();
   window_->Draw(sprite_);
   window_->Display();
   
}
