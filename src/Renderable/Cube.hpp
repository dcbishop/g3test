#ifndef G3TEST_CUBE_HPP_
#define G3TEST_CUBE_HPP_

#include <vector>
using std::vector;

#include <glm/glm.hpp>

#define GL3_PROTOTYPES
#include <GL3/gl3.h>
#include <GL/freeglut.h>

#include "../OpenGL/VertexArray.hpp"
#include "../OpenGL/Buffer.hpp"

class Cube {
   public:
      Cube();
      ~Cube();
      void init();
      void deinit();
      void render();

   private:
      glm::vec3 position_;
      VertexArray array_;
      Buffer buffer_;
      static bool isInitilized_;
};

#endif /* G3TEST_CUBE_HPP_ */
