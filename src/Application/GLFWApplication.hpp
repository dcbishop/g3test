#ifndef G3TEST_GLFWAPPLICATION_HPP_
#define G3TEST_GLFWAPPLICATION_HPP_

class DemoScene;

class GLFWApplication {
   public:
      GLFWApplication();
      ~GLFWApplication();

      void setSize(const int width, const int height);
      void run();
      void update();
      void render();

   private:
      DemoScene* demo_scene_;
      int width_;
      int height_;
};

#endif /* G3TEST_GLFWAPPLICATION_HPP_ */
