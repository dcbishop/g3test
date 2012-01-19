#ifndef G3TEST_PROGRAM_HPP_
#define G3TEST_PROGRAM_HPP_

#include <set>
#include <memory>

#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Shader.hpp"

#include <glm/glm.hpp>

typedef std::set<ShaderPtr> ShaderList;
class Program {
   public:
      Program();
      ~Program();
      void attach(ShaderPtr shader);
      void detach(ShaderPtr shader);
      void attach(Shader& shader);
      void detach(Shader& shader);
      GLuint getUniformLocation(const GLchar* name);
      void bindAttribLocation(const GLuint index, const GLchar* name);
      void uniformMatrix(const glm::mat4& matrix, const GLuint index);
      void uniformMatrix(const glm::mat3& matrix, const GLuint index);

      void uniform(const GLfloat& v0, const GLuint& index);
      void uniform(const glm::vec2& v, const GLuint& index);
      void uniform(const glm::vec3& v, const GLuint& index);
      void uniform(const glm::vec4& v, const GLuint& index);

      void link();
      void use();
      static void unuse();
      void debugLog() const;


   private:
      GLuint program_id_;
      ShaderList shaders_;
};

typedef std::shared_ptr<Program> ProgramPtr;

inline GLuint Program::getUniformLocation(const GLchar* name) {
   GLuint location = glGetUniformLocation(program_id_, name);
   logGLError();
   return location;
}

inline void Program::bindAttribLocation(const GLuint index, const GLchar* name) {
   glBindAttribLocation(program_id_, index, name);
   logGLError();
}

inline void Program::uniformMatrix(const glm::mat4& matrix, const GLuint index) {
   glUniformMatrix4fv(index, 1, GL_FALSE, &matrix[0][0]);
   logGLError();
}

inline void Program::uniformMatrix(const glm::mat3& matrix, const GLuint index) {
   glUniformMatrix3fv(index, 1, GL_FALSE, &matrix[0][0]);
   logGLError();
}

inline void Program::uniform(const GLfloat& v0, const GLuint& index) {
   glUniform1f(index, v0);
}

inline void Program::uniform(const glm::vec2& v, const GLuint& index) {
   glUniform2f(index, v[0], v[1]);
}

inline void Program::uniform(const glm::vec3& v, const GLuint& index) {
   glUniform3f(index, v[0], v[1], v[2]);
}

inline void Program::uniform(const glm::vec4& v, const GLuint& index) {
   glUniform4f(index, v[0], v[1], v[2], v[3]);
}

inline void Program::use() {
   glUseProgram(program_id_);
   logGLError();
}

inline void Program::unuse() {
   glUseProgram(0);
}

#endif /* G3TEST_PROGRAM_HPP_ */
