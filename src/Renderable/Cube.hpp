#ifndef GL3TEST_CUBE_HPP_
#define GL3TEST_CUBE_HPP_

#include <glm/glm.hpp>

class Cube {
   public:
      Cube();      
      void render();

   private:
      glm::vec3 position_;
      VertexArray array_;
      Buffer buffer_;
};

#endif /* GL3TEST_CUBE_HPP_ */
