#ifndef G3TEST_PROGRAM_HPP_
#define G3TEST_PROGRAM_HPP_

#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Shader.hpp"


class Program {
   public:
      Program() {
         program_id_ = glCreateProgram();
         logGLError();
      }

      ~Program() {
         glDeleteProgram(program_id_);
         logGLError();
      }

      void attach(Shader& shader) {
         glAttachShader(program_id_, shader.getShaderId());
         logGLError();
      }
      
      void detach(Shader& shader) {
         glAttachShader(program_id_, shader.getShaderId());
         logGLError();
      }

      GLuint getUniformLocation(const GLchar* name) {
         GLuint location = glGetUniformLocation(program_id_, name);
         logGLError();
         return location;
      }

      void bindAttribLocation(const GLuint index, const GLchar* name) {
         glBindAttribLocation(program_id_, index, name);
         logGLError();
      }

      void uniformMatrix(const glm::mat4& matrix, const GLuint index) {
         glUniformMatrix4fv(index, 1, GL_FALSE, &matrix[0][0]);
         logGLError();
         /*GLint current;
         glGetIntegerv(GL_CURRENT_PROGRAM, &current);
         DEBUG_M("%d == %d", program_id_, current);*/
      }

      void link() {
         glLinkProgram(program_id_);
         logGLError();
      }
      
      void use() {
         glUseProgram(program_id_);
         logGLError();
      }
      
      static void unuse() {
         glUseProgram(0);
      }

   private:
      GLuint program_id_;
};

#endif /* G3TEST_PROGRAM_HPP_ */
