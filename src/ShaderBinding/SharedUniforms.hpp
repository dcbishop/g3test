#ifndef G3_SHAREDUNIFORMS_HPP_
#define G3_SHAREDUNIFORMS_HPP_

#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Buffer.hpp"
#include "../Main/Globals.hpp"
#include "../Main/ResourceManager.hpp"

#include <glm/glm.hpp>
#include <unordered_map>

class SharedUniforms : public Buffer {
   public:
      SharedUniforms();
      void setModelViewMatrix(const glm::mat4& mv_matrix);
      void setProjectionMatrix(const glm::mat4& mv_matrix);
      void setModelViewProjectionMatrix(const glm::mat4& mvp_matrix);
      void setNormalMatrix(const glm::mat3& normal_matrix);
      void setResolution(const glm::vec2& resolution);
      void setTime(const GLfloat& time);
      void updateAll();

      g3::GLsizeiptr getSize() const;
      GLuint getBlockIndex() const;
      GLuint getBindingPoint() const;
      GLuint getBlockSize() const;
      void setBlockSize(const GLuint size);
      void setBlockIndex(const GLuint index);
      void bindTo(const ProgramPtr& program) const;

   private:
      struct Uniform {
         GLuint index;
         std::string name;
         GLint offset;
         GLint size;
      };

      struct Shared {
         glm::mat4 MVMatrix;
         glm::mat4 ProjectionMatrix;
         glm::mat4 MVPMatrix;
         glm::mat3 NormalMatrix;
         glm::vec2 resolution;
         GLfloat time;
      };

      Shared shared_;
      std::unordered_map<std::string, Uniform> uniforms_;

      GLuint ub_index_;
      GLint ub_size_;
};

inline SharedUniforms::SharedUniforms() {
   setTarget(Buffer::Uniform);
   bind();

   ProgramPtr dummy_program_ = globals.getResourceManager().getVFProgram("UBODummy.vert", "UBODummy.frag");

   // Get the global index of the uniform Block
   setBlockIndex(dummy_program_->getUniformBlockIndex("SharedUniforms"));
   if(getBlockIndex() == -1) {
      ERROR("Failed to find the uniform block index in shader.");
      setBlockSize(0);
      data(0, nullptr, Buffer::StreamDraw);
      return;
   }

   // Set the block binding point for the shader program
   dummy_program_->uniformBlockBinding(getBlockIndex(), getBindingPoint());
   
   // Get the size of the uniform block
   dummy_program_->getActiveUniformBlock(getBlockIndex(), Program::UniformBlockDataSize, &ub_size_);

   // Get the number of active uniforms in the block
   GLint num_uniforms;
   dummy_program_->getActiveUniformBlock(getBlockIndex(), Program::UniformBlockActiveUniforms, &num_uniforms);

   // Get the length of the uniform block's name
   GLsizei block_name_length; 
   dummy_program_->getActiveUniformBlock(getBlockIndex(), Program::UniformBlockNameLength, &block_name_length);

   // Get the uniform block's name
   std::vector<GLchar> block_name(block_name_length);
   dummy_program_->getActiveUniformBlockName(getBlockIndex(), block_name_length, nullptr, &block_name.front());

   // Get list of indicies in uniform block
   std::vector<GLint> indices(num_uniforms);
   dummy_program_->getActiveUniformBlock(getBlockIndex(), Program::UniformBlockActiveUniformIndices, &indices.front());

   for(int i = 0; i < num_uniforms; i++) {
      // Get length of uniform name
      GLsizei uniform_name_length;
      dummy_program_->getActiveUniforms(1, (GLuint*)&indices.at(i), Program::UniformNameLength, &uniform_name_length);

      // Get uniform name
      std::vector<GLchar> uniform_name(uniform_name_length);
      dummy_program_->getActiveUniformName(indices.at(i), uniform_name_length, nullptr, &uniform_name.front());

      // Get uniform offset
      GLint uniform_offset;
      dummy_program_->getActiveUniforms(1, (GLuint*)&indices.at(i), Program::UniformOffset, &uniform_offset);

      // Get size of uniform
      GLint uniform_size;
      dummy_program_->getActiveUniforms(1, (GLuint*)&indices.at(i), Program::UniformSize, &uniform_size);

      // Create a Uniform object and add it to the list
      std::string uniform_name_str(&uniform_name.front());
      Uniform uniform {indices.at(i), uniform_name_str, uniform_offset, uniform_size};
      uniforms_[uniform_name_str] = uniform;

      DEBUG_M("Uniforms in block: %d, %s, %d, %d", uniform.index, uniform.name.c_str(), uniform.offset, uniform.size);
   }

   data(getSize(), nullptr, Buffer::StreamDraw);
   bindRange(getBindingPoint(), 0, getSize());
   unbind();
}

inline GLuint SharedUniforms::getBlockIndex() const {
   return ub_index_;
}

inline GLuint SharedUniforms::getBindingPoint() const {
   return 0;
}

inline GLuint SharedUniforms::getBlockSize() const {
   return ub_size_;
}

inline void SharedUniforms::setBlockSize(const GLuint size) {
   ub_size_ = size;
}

inline void SharedUniforms::setBlockIndex(const GLuint index) {
   ub_index_ = index;
}

inline void SharedUniforms::updateAll() {
   bind();
   subData(0, getSize(), &shared_);
}

inline void SharedUniforms::setModelViewMatrix(const glm::mat4& mv_matrix) {
   if(uniforms_.size() < 1) {
      return;
   }
   bind();
   static g3::GLintptr offset = uniforms_.at("MVMatrix").offset;
   static g3::GLsizeiptr size = sizeof(mv_matrix);
   subData(offset, size, &mv_matrix[0][0]);
}

inline void SharedUniforms::setProjectionMatrix(const glm::mat4& projection_matrix) {
   if(uniforms_.size() < 2) {
      return;
   }
   bind();
   static g3::GLintptr offset = uniforms_.at("ProjectionMatrix").offset;
   static g3::GLsizeiptr size = sizeof(projection_matrix);
   subData(offset, size, &projection_matrix[0][0]);
}

inline void SharedUniforms::setModelViewProjectionMatrix(const glm::mat4& mvp_matrix) {
   if(uniforms_.size() < 3) {
      return;
   }
   bind();
   static g3::GLintptr offset = uniforms_.at("MVPMatrix").offset;
   static g3::GLsizeiptr size = sizeof(mvp_matrix);
   subData(offset, size, &mvp_matrix[0][0]);
}

inline void SharedUniforms::setNormalMatrix(const glm::mat3& normal_matrix) {
   if(uniforms_.size() < 4) {
      return;
   }
   bind();
   static g3::GLintptr offset = uniforms_.at("NormalMatrix").offset;
   static g3::GLsizeiptr size = sizeof(normal_matrix);
   subData(offset, size, &normal_matrix[0][0]);
}

inline void SharedUniforms::setResolution(const glm::vec2& resolution) {
   if(uniforms_.size() < 5) {
      return;
   }
   bind();
   static g3::GLintptr offset = uniforms_.at("resolution").offset;
   static g3::GLsizeiptr size = sizeof(resolution);
   subData(offset, size, &resolution[0]);
}

inline void SharedUniforms::setTime(const GLfloat& time) {
   if(uniforms_.size() < 6) {
      return;
   }
   bind();
   static g3::GLintptr offset = uniforms_.at("time").offset;
   static g3::GLsizeiptr size = sizeof(time);
   subData(offset, size, &time);
}

inline g3::GLsizeiptr SharedUniforms::getSize() const {
   return ub_size_;
}

inline void SharedUniforms::bindTo(const ProgramPtr& program) const {
   program->uniformBlockBinding(getBlockIndex(), getBindingPoint());
}

#endif /* G3_SHAREDUNIFORMS_HPP_ */
