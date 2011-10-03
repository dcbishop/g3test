#ifndef G3TEST_CUBE_HPP_
#define G3TEST_CUBE_HPP_

#include <glm/glm.hpp>

#include "../OpenGL/OpenGL.hpp"
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
      glm::vec4 rotation_;
      VertexArray array_;
      Buffer buffer_;
      static bool isInitilized_;
};

#endif /* G3TEST_CUBE_HPP_ */
