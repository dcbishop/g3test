#ifndef G3_GLUTAPPLICATION_HPP_
#define G3_GLUTAPPLICATION_HPP_

class DemoScene;

class GLUTApplication {
   public:
      GLUTApplication(int& argc, char* argv[]);
      ~GLUTApplication();
      static void setSize(const int width, const int height);
      void run();

      static DemoScene* demo_scene_;
};

void render_(void);
void resize_(int w, int h);
void timer_(int);
void idle_(void);

#endif /* G3_GLUTAPPLICATION_HPP_ */
