#include "Program.hpp"

#include "../Debug/console.h"

Program::Program() {
   program_id_ = glCreateProgram();
   logGLError();
}

Program::~Program() {
   glDeleteProgram(program_id_);
   logGLError();
}

void Program::attach(ShaderPtr shader) {
   DEBUG_M("Attaching shader '%d' to program '%d'", shader->getShaderId(), program_id_);
   if(shader == ShaderPtr()) {
      ERROR("Tried to attach NULL shader.");
      return;
   }
   glAttachShader(program_id_, shader->getShaderId());
   shaders_.insert(shader);
}

void Program::detach(ShaderPtr shader) {
   ShaderList::iterator itr = shaders_.find(shader);
   shaders_.erase(itr);
   detach(shader);
}

void Program::attach(Shader& shader) {
   // TODO: Remove me? To force use of ShaderPtr
   glAttachShader(program_id_, shader.getShaderId());
   logGLError();
}

void Program::detach(Shader& shader) {
   glAttachShader(program_id_, shader.getShaderId());
   logGLError();
}

void Program::link() {
   glLinkProgram(program_id_);
   logGLError();
}

void Program::debugLog() const {
   int length = 0;
   glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &length);
   if(length <= 0) {
      DEBUG_M("No log");
      return;
   }

   std::vector<char> program_log;
   program_log.resize(length);
   glGetProgramInfoLog(program_id_, length, &length, &program_log[0]);
   if(length > 0) {
      LOG("ShaderLog: %s", &program_log[0]);
   }
}
