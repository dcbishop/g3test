#ifndef G3TEST_SFMLAPPLICATION_HPP_
#define G3TEST_SFMLAPPLICATION_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class DemoScene;

class SFMLApplication {
   public:
      SFMLApplication();
      ~SFMLApplication();
      void run();

   private:
      void processEvents_();
      void render_();

      sf::RenderWindow* window_;
      bool isRunning_;
      DemoScene* demo_scene_;
};

#endif /* G3TEST_SFMLAPPLICATION_HPP_ */
