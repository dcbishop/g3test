#ifndef G3_SHADERMANAGER_HPP_
#define G3_SHADERMANAGER_HPP_

#include <vector>
#include <memory>
#include "SharedUniforms.hpp"


//TODO: 
class ShaderManager {
   public:
      enum Mode {
         Basic,
         FlatTexture,
         Grid,
         EdgeDetect,
         Pixelate,
         MaxModes
      };

      ShaderManager();
      void setMode(const Mode& mode);
      void setUniform(const SharedUniforms::Uniform uniform_name, const glm::mat4& value);
      void setUniform(const SharedUniforms::Uniform uniform_name, const glm::mat3& value);
      void setUniform(const SharedUniforms::Uniform uniform_name, const glm::vec2& value);
      void setUniform(const SharedUniforms::Uniform uniform_name, const GLfloat& value);

      ProgramPtr getProgram(const Mode mode) const;
      SharedUniforms& getSharedUniforms();

   private:
      std::vector<ProgramPtr> shaders_;
      SharedUniforms ubo_;
};

typedef std::shared_ptr<ShaderManager> ShaderManagerPtr;

inline ShaderManager::ShaderManager() {
   logGLError();
   ResourceManager& rm =  globals.getResourceManager();
   logGLError();
   shaders_.push_back(rm.getVFProgram("Basic.vert", "Basic.frag"));
   shaders_.push_back(rm.getVFProgram("FlatTexture.vert", "FlatTexture.frag"));
   shaders_.push_back(rm.getVFProgram("FlatTexture.vert", "Grid.frag"));
   shaders_.push_back(rm.getVFProgram("FlatTexture.vert", "EdgeDetect.frag"));
   shaders_.push_back(rm.getVFProgram("FlatTexture.vert", "Pixelate.frag"));
   shaders_.push_back(rm.getVFProgram("FlatTexture.vert", "TextureTunnel.frag"));
   logGLError();
   for(ProgramPtr program: shaders_) {
      logGLError();
      ubo_.bindTo(program);
      logGLError();
   }
}

inline void ShaderManager::setMode(const Mode& mode) {
   if(mode < shaders_.size()) {
      shaders_[mode]->use();
   }
}

inline void ShaderManager::setUniform(const SharedUniforms::Uniform uniform_name, const glm::mat4& value) {
   ubo_.setUniform(uniform_name, value);
}

inline void ShaderManager::setUniform(const SharedUniforms::Uniform uniform_name, const glm::mat3& value) {
   ubo_.setUniform(uniform_name, value);
}

inline void ShaderManager::setUniform(const SharedUniforms::Uniform uniform_name, const glm::vec2& value) {
   ubo_.setUniform(uniform_name, value);
}

inline void ShaderManager::setUniform(const SharedUniforms::Uniform uniform_name, const GLfloat& value) {
   ubo_.setUniform(uniform_name, value);
}

inline SharedUniforms& ShaderManager::getSharedUniforms() {
   return ubo_;
}

inline ProgramPtr ShaderManager::getProgram(const Mode mode) const {
   return shaders_[mode];
};


#endif /* G3_SHADERMANAGER_HPP_ */
