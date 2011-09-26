#ifndef SFMLTEST_APPLICATION_HPP_
#define SFMLTEST_APPLICATION_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Application {
   public:
      Application();
      void run();

   private:
      void processEvents_();
      void render_();

      sf::RenderWindow* window_;
      sf::Sprite sprite_;
      bool isRunning_;
};

#endif /* SFMLTEST_APPLICATION_HPP_ */
