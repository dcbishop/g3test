#ifndef G3TEST_ERRORMESH_HPP_
#define G3TEST_ERRORMESH_HPP_

#include "../OpenGL/VertexArray.hpp"
#include "../OpenGL/Buffer.hpp"

/**
 * A ERROR placeholder mesh
 */
class ErrorMesh {
   public:
      ErrorMesh();
      ~ErrorMesh();
      void init();
      void render();

   private:
      static bool isInitilized_;

      VertexArray array_0;
      VertexArray array_1;
      VertexArray array_2;
      /*Buffer vertices_buffer_;
      Buffer indices1_buffer_;
      Buffer indices2_buffer_;
      Buffer indices3_buffer_;*/
      Buffer vertices_buffer_0;
      Buffer vertices_buffer_1;
      Buffer vertices_buffer_2;
};

#endif /* G3TEST_ERRORMESH_HPP_ */
