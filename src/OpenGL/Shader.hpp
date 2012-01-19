#ifndef G3TEST_SHADER_HPP_
#define G3TEST_SHADER_HPP_

#include <vector>
#include <memory>

#include "../OpenGL/OpenGL.hpp"

class Shader {
   public:
      enum Type: GLenum {
         Vertex         = GL_VERTEX_SHADER,
         TessControl    = GL_TESS_CONTROL_SHADER,
         TessEvaluation = GL_TESS_EVALUATION_SHADER,
         Geometry       = GL_GEOMETRY_SHADER,
         Fragment       = GL_FRAGMENT_SHADER
      };

      Shader(const Type type, std::vector<char> source_code);
      Shader(const Type type, const char* source_code = nullptr, const GLint size=0);
      ~Shader();
      void compile();
      void source(const std::vector<char>& source_code);
      void source(const char* source_code, const GLint size);
      void debugLog() const;
      GLuint getShaderId() const;

   private:
      void init_(const Type type, const char* source_code = nullptr, const GLint size=0);

      GLuint shader_id_;
      const Type type_;
      bool has_source_;
};

typedef std::shared_ptr<Shader> ShaderPtr;

#endif /* G3TEST_SHADER_HPP_ */
