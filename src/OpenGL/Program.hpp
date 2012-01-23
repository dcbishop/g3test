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
      enum Paramater: GLenum {
         UniformBlockBinding = GL_UNIFORM_BLOCK_BINDING,
         UniformBlockDataSize = GL_UNIFORM_BLOCK_DATA_SIZE,
         UniformBlockNameLength = GL_UNIFORM_BLOCK_NAME_LENGTH,
         UniformBlockActiveUniforms = GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
         UniformBlockActiveUniformIndices = GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
         UniformBlockRefrencedByVertexShader = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,
         UniformBlockRefrencedByGeometryShader = GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER,
         UniformBlockRefrencedByFragmentShader = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER,
         UniformType = GL_UNIFORM_TYPE,
         UniformSize = GL_UNIFORM_SIZE,
         UniformNameLength = GL_UNIFORM_NAME_LENGTH,
         UniformBlockIndex = GL_UNIFORM_BLOCK_INDEX,
         UniformOffset = GL_UNIFORM_OFFSET,
         UniformArrayStride = GL_UNIFORM_ARRAY_STRIDE,
         UniformMatrixStride = GL_UNIFORM_MATRIX_STRIDE,
         UniformIsRowMajor = GL_UNIFORM_IS_ROW_MAJOR,
#ifdef GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX
         UniformAtomicCounterBuffer = GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX
#endif
      };

      Program();
      ~Program();
      void attach(ShaderPtr shader);
      void detach(ShaderPtr shader);
      void attach(Shader& shader);
      void detach(Shader& shader);
      GLuint getProgramId() const;
      void setProgramId(const GLuint program_id);

      GLuint getUniformLocation(const GLchar* name);
      GLuint getUniformBlockIndex(const GLchar* uniformBlockName) const;
      void getActiveUniformBlock(const GLuint& uniformBlockIndex, const Paramater& pname, GLint* params) const;
      void getActiveUniformBlockName(const GLuint uniformBlockIndex, const GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) const;
      GLuint getUniformIndices(const GLsizei uniformCount, const GLchar **uniformNames, GLuint *uniformIndices) const; 
      void getActiveUniform(const GLuint& index, const GLsizei& bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) const;
      void getActiveUniformName(const GLuint& uniformIndex, const GLsizei& bufSize, GLsizei* length, GLchar* uniformName) const;
      void getActiveUniforms(const GLsizei& uniformCount, const GLuint* uniformIndices, const Paramater& pname, GLint* params) const;

      void uniformBlockBinding(const GLuint& uniformBlockIndex, const GLuint& uniformBlockBinding);
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

inline GLuint Program::getProgramId() const {
   return program_id_;
}

inline void Program::setProgramId(const GLuint program_id) {
   program_id_ = program_id;
}

inline GLuint Program::getUniformLocation(const GLchar* name) {
   use();
   GLuint location = glGetUniformLocation(getProgramId(), name);
   logGLError();
   return location;
}

inline GLuint Program::getUniformBlockIndex(const GLchar* uniformBlockName) const {
   return glGetUniformBlockIndex(getProgramId(), uniformBlockName);
}

inline GLuint Program::getUniformIndices(const GLsizei uniformCount, const GLchar **uniformNames, GLuint *uniformIndices) const {
   glGetUniformIndices(getProgramId(), uniformCount, uniformNames, uniformIndices);
   // Glew 1.6 seems to have this defined differntly to the specs :/
   //glGetUniformIndices(uniformCount, uniformNames, uniformIndices);
}

inline void Program::getActiveUniform(const GLuint& index, const GLsizei& bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) const {
   glGetActiveUniform(getProgramId(), index, bufSize, length, size, type, name);
}

inline void Program::getActiveUniformName(const GLuint& uniformIndex, const GLsizei& bufSize, GLsizei* length, GLchar* uniformName) const {
   glGetActiveUniformName(getProgramId(), uniformIndex, bufSize, length, uniformName);
}

inline void Program::getActiveUniforms(const GLsizei& uniformCount, const GLuint* uniformIndices, const Paramater& pname, GLint* params) const {
   glGetActiveUniformsiv(getProgramId(), uniformCount, uniformIndices, pname, params);
}

inline void Program::uniformBlockBinding(const GLuint& uniformBlockIndex, const GLuint& uniformBlockBinding) {
   glUniformBlockBinding(getProgramId(), uniformBlockIndex, uniformBlockBinding);
}

inline void Program::getActiveUniformBlock(const GLuint& uniformBlockIndex, const Paramater& pname, GLint* params) const {
   glGetActiveUniformBlockiv(getProgramId(), uniformBlockIndex, pname, params);
}

inline void Program::getActiveUniformBlockName(const GLuint uniformBlockIndex, const GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) const {
   glGetActiveUniformBlockName(getProgramId(), uniformBlockIndex, bufSize, length, uniformBlockName);
}

inline void Program::bindAttribLocation(const GLuint index, const GLchar* name) {
   use();
   glBindAttribLocation(program_id_, index, name);
   logGLError();
}

inline void Program::uniformMatrix(const glm::mat4& matrix, const GLuint index) {
   use();
   glUniformMatrix4fv(index, 1, GL_FALSE, &matrix[0][0]);
   logGLError();
}

inline void Program::uniformMatrix(const glm::mat3& matrix, const GLuint index) {
   use();
   glUniformMatrix3fv(index, 1, GL_FALSE, &matrix[0][0]);
   logGLError();
}

inline void Program::uniform(const GLfloat& v0, const GLuint& index) {
   use();
   glUniform1f(index, v0);
}

inline void Program::uniform(const glm::vec2& v, const GLuint& index) {
   use();
   glUniform2f(index, v[0], v[1]);
}

inline void Program::uniform(const glm::vec3& v, const GLuint& index) {
   use();
   glUniform3f(index, v[0], v[1], v[2]);
}

inline void Program::uniform(const glm::vec4& v, const GLuint& index) {
   use();
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
