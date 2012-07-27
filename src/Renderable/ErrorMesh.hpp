#ifndef G3TEST_ERRORMESH_HPP_
#define G3TEST_ERRORMESH_HPP_

#include <vector>

#include <dglw/dglw.hpp>

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
      static std::vector<dglw::VertexArrayPtr> array_;
      static std::vector<dglw::BufferPtr> vertices_buffer_;
      static dglw::ProgramPtr program_;
};

inline void ErrorMesh::render() {
   using namespace dglw;

   glDisable(GL_CULL_FACE);
   
   program_->use();

   static unsigned int number_of_triangles_0 = vertices_buffer_[0]->getBufferSize()/sizeof(float)*3;
   static unsigned int number_of_triangles_1 = vertices_buffer_[1]->getBufferSize()/sizeof(float)*3;
   static unsigned int number_of_triangles_2 = vertices_buffer_[2]->getBufferSize()/sizeof(float)*3;

   const static glm::vec4 white_color(1.0f, 1.0f, 1.0f, 1.0f);
   const static glm::vec4 red_color(1.0f, 0.0f, 0.0f, 1.0f);
   const static glm::vec4 no_color(0.0f, 0.0f, 0.0f, 0.0f);
   const static GLuint color_loc = program_->getUniformLocation("color_overide");

   program_->uniform(white_color, color_loc);
   array_[0]->draw();
   array_[1]->draw();

   program_->uniform(red_color, color_loc);
   array_[2]->draw();

   program_->uniform(no_color, color_loc);
   
   VertexArray::unbind();
   logGLError();
}

#endif /* G3TEST_ERRORMESH_HPP_ */
