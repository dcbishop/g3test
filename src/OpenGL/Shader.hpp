#ifndef G3TEST_SHADER_HPP_
#define G3TEST_SHADER_HPP_

#include <vector>

#include "../OpenGL/OpenGL.hpp"

class Shader {
   public:
      enum Type {
         Vertex = GL_VERTEX_SHADER,
         TessControl = GL_TESS_CONTROL_SHADER,
         TessEvaluation = GL_TESS_EVALUATION_SHADER,
         Geometry = GL_GEOMETRY_SHADER,
         Fragment = GL_FRAGMENT_SHADER
      };

      Shader(const Type type, std::vector<char> source_code): type_(type) {
         init_(type, &source_code[0], source_code.size());
      }

      Shader(const Type type, const char* source_code = nullptr, const GLint size=0): type_(type) {
         init_(type, source_code, size);
      }
      
      ~Shader() {
         DEBUG_M("Deconstructing shader %d", shader_id_);
         glDeleteShader(shader_id_);
      }

      void compile() {
         glCompileShader(shader_id_);
         logGLError();
      }

      void source(const std::vector<char>& source_code) {
         source(&source_code[0], source_code.size());
         logGLError();
      }

      void source(const char* source_code, const GLint size) {
         glShaderSource(shader_id_, 1, (const GLchar**)&source_code, &size);
         has_source_ = true;
         logGLError();
      }
      
      void debugLog() {
         int length = 0;
         glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &length);
         if(length <= 0) {
            return;
         }

         std::vector<char> shader_log;
         shader_log.resize(length);
         glGetShaderInfoLog(shader_id_, length, &length, &shader_log[0]);
         if(length > 0) {
            LOG("ShaderLog: %s", &shader_log[0]);
         }
      }

      GLuint getShaderId() const {
         return shader_id_;
      }

   private:
      void init_(const Type type, const char* source_code = nullptr, const GLint size=0) {
         shader_id_ = glCreateShader(type);
         logGLError();

         if(source_code != nullptr && size > 0) {
            source(source_code, size);
         } else {
            has_source_ = false;
         }         
      }

      GLuint shader_id_;
      const Type type_;
      bool has_source_;
};

#endif /* G3TEST_SHADER_HPP_ */
