#include "Shader.hpp"

Shader::Shader(const Type type, std::vector<char> source_code): type_(type) {
   DEBUG_M("Making Shader from vector<char> %d", source_code.size());
   if(source_code.size() == 0) {
      ERROR("Tried to construct shader with empty source...");
      return;
   }
      
   init_(type, &source_code[0], source_code.size());
}

Shader::Shader(const Type type, const char* source_code, const GLint size): type_(type) {
   DEBUG_M("Making Shader from const char*");
   init_(type, source_code, size);
}

Shader::~Shader() {
   DEBUG_M("Deconstructing shader %d", shader_id_);
   glDeleteShader(shader_id_);
}

void Shader::compile() {
   if(!has_source_) {
      ERROR("Trying to compile shader without source.");
      return;
   }
   glCompileShader(shader_id_);
   logGLError();
   debugLog();
}

void Shader::source(const std::vector<char>& source_code) {
   source(&source_code[0], source_code.size());
   logGLError();
}

void Shader::source(const char* source_code, const GLint size) {
   DEBUG_M("Shader source.");
   glShaderSource(shader_id_, 1, (const GLchar**)&source_code, &size);
   has_source_ = true;
   logGLError();
   debugLog();
}

void Shader::debugLog() const {
   int length = 0;
   glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &length);
   if(length <= 0) {
      DEBUG_M("No log");
      return;
   }

   std::vector<char> shader_log;
   shader_log.resize(length);
   glGetShaderInfoLog(shader_id_, length, &length, &shader_log[0]);
   if(length > 0) {
      LOG("ShaderLog: %s", &shader_log[0]);
   }
}

GLuint Shader::getShaderId() const {
   return shader_id_;
}

void Shader::init_(const Type type, const char* source_code, const GLint size) {
   shader_id_ = glCreateShader(type);
   DEBUG_M("Created shader %d", shader_id_);
   logGLError();

   if(source_code != nullptr && size > 0) {
      source(source_code, size);
   } else {
      has_source_ = false;
   }         
}
