#ifndef G3TEST_ERRORMESH_HPP_
#define G3TEST_ERRORMESH_HPP_

#include <vector>

#include "../OpenGL/VertexArray.hpp"
#include "../OpenGL/Buffer.hpp"
#include "../OpenGL/Program.hpp"

/**
 * A ERROR placeholder mesh
 */
class ErrorMesh {
   public:
      ErrorMesh();
      ~ErrorMesh();
      void render();

   private:
      void init_();
      void deinit_();

      static bool isInitilized_;
      static unsigned int refs_;

      const static unsigned int num_meshes_;
      static std::vector<VertexArrayPtr> array_;
      static std::vector<BufferPtr> vertices_buffer_;
      static ProgramPtr program_;
};

#endif /* G3TEST_ERRORMESH_HPP_ */
