#ifndef G3TEST_SHADER_HPP_
#define G3TEST_SHADER_HPP_

#define GL3_PROTOTYPES
#include <GL3/gl3.h>

class Shader {
   public:
      enum Type {
         Vertex = GL_VERTEX_SHADER,
         TessControl = GL_TESS_CONTROL_SHADER,
         TessEvaluation = GL_TESS_EVALUATION_SHADER,
         Geometry = GL_GEOMETRY_SHADER,
         Fragment = GL_FRAGMENT_SHADER
      };

      Shader(const Type type, const char* source_code = nullptr, const GLint size=0): type_(type) {
         shader_id_ = glCreateShader(type);
         if(source_code != nullptr && size > 0) {
            source(source_code, size);
         } else {
            has_source_ = false;
         }
      }

      ~Shader() {
         glDeleteShader(shader_id_);
      }

      void compile() {
         glCompileShader(shader_id_);
      }

      void source(const char* source, const GLint size) {
         glShaderSource(shader_id_, 1, (const GLchar**)&source, &size);
         has_source_ = true;
      }

      GLuint getShaderId() const {
         return shader_id_;
      }

   private:
      GLuint shader_id_;
      const Type type_;
      bool has_source_;
};

#endif /* G3TEST_SHADER_HPP_ */
