#ifndef G3TEST_PROGRAM_HPP_
#define G3TEST_PROGRAM_HPP_

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

class Program {
   public:
      Program() {
         program_id_ = glCreateProgram();
      }
      
      ~Program() {
         glDeleteProgram(program_id_);
      }

      void attach(Shader& shader) {
         glAttachShader(program_id_, shader.getShaderId());
      }
      
      void detach(Shader& shader) {
         glAttachShader(program_id_, shader.getShaderId());
      }
      
      void link() {
         glLinkProgram(program_id_);
      }
      
      void use() {
         glUseProgram(program_id_);
      }

   private:
      GLuint program_id_;
};

#endif /* G3TEST_PROGRAM_HPP_ */
