#ifndef G3_SHAREDUNIFORMS_HPP_
#define G3_SHAREDUNIFORMS_HPP_

#include "../OpenGL/OpenGL.hpp"
#include "../OpenGL/Buffer.hpp"
#include "../Main/Globals.hpp"
#include "../Main/ResourceManager.hpp"

#include <glm/glm.hpp>
#include <unordered_map>


// TODO: This class is unstable if some shaders don't load.
class SharedUniforms : public Buffer {
   public:
      // This must be kept in sync with SharedUniforms.cpp and GLSL code
      enum Uniform {
         MVMatrix,
         ProjectionMatrix,
         MVPMatrix,
         ViewPort,
         NormalMatrix,
         Resolution,
         Time,
         MaxUniform
      };

      SharedUniforms();

      void setUniform(const Uniform uniform, const glm::mat4& value);
      void setUniform(const Uniform uniform, const glm::mat3& value);
      void setUniform(const Uniform uniform, const glm::vec2& value);
      void setUniform(const Uniform uniform, const GLfloat& value);

      g3::GLsizeiptr getSize() const;
      GLuint getBlockIndex() const;
      GLuint getBindingPoint() const;
      GLuint getBlockSize() const;
      void setBlockSize(const GLuint size);
      void setBlockIndex(const GLuint index);
      void bindTo(const ProgramPtr& program) const;
      static LookupNames UniformNames;

   private:
      struct UniformInfo {
         GLuint index;
         std::string name;
         GLint offset;
         GLint size;
      };

      /*struct Shared {
         glm::mat4 MVMatrix;
         glm::mat4 ProjectionMatrix;
         glm::mat4 MVPMatrix;
         glm::mat3 NormalMatrix;
         glm::vec2 resolution;
         GLfloat time;
      };

      Shared shared_;*/
      std::unordered_map<std::string, UniformInfo> uniforms_;
      std::vector<unsigned int> uniform_index_;
      std::vector<unsigned int> uniform_offsets_;
      static std::string uniform_block_name;

      GLuint ub_index_;
      GLint ub_size_;
};

inline SharedUniforms::SharedUniforms() {
   logGLError();
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
   logGLError();
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
   logGLError();
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
      UniformInfo uniform {indices.at(i), uniform_name_str, uniform_offset, uniform_size};
      uniforms_[uniform_name_str] = uniform;

      DEBUG_M("Uniforms in block: %d, %s, %d, %d", uniform.index, uniform.name.c_str(), uniform.offset, uniform.size);
   }

   data(getSize(), nullptr, Buffer::StreamDraw);
   bindRange(getBindingPoint(), 0, getSize());
   unbind();
   logGLError();

   // We should have found all the uniforms in the central list...
   if(uniforms_.size() < MaxUniform) {
      ERROR("Failed to find all uniforms.");
      uniform_index_.resize(MaxUniform);
      uniform_offsets_.resize(MaxUniform);
      return;
   }

   // Add the uniform id's to a vector for quick indexed retrieval...
   uniform_index_.resize(uniforms_.size());
   uniform_index_[MVMatrix] = std::distance(uniforms_.begin(), uniforms_.find("MVMatrix"));
   uniform_index_[ProjectionMatrix] = std::distance(uniforms_.begin(), uniforms_.find("ProjectionMatrix"));
   uniform_index_[MVPMatrix] = std::distance(uniforms_.begin(), uniforms_.find("MVPMatrix"));
   uniform_index_[ViewPort] = std::distance(uniforms_.begin(), uniforms_.find("ViewportMatrix"));
   uniform_index_[NormalMatrix] = std::distance(uniforms_.begin(), uniforms_.find("NormalMatrix"));
   uniform_index_[Resolution] = std::distance(uniforms_.begin(), uniforms_.find("resolution"));
   uniform_index_[Time] = std::distance(uniforms_.begin(), uniforms_.find("time"));

   // Add the uniform offsets to a vector for quick indexed retrieval...
   uniform_offsets_.resize(uniforms_.size());
   uniform_offsets_[MVMatrix] = uniforms_.at("MVMatrix").offset;
   uniform_offsets_[ProjectionMatrix] = uniforms_.at("ProjectionMatrix").offset;
   uniform_offsets_[MVPMatrix] = uniforms_.at("MVPMatrix").offset;
   uniform_offsets_[ViewPort] = uniforms_.at("ViewportMatrix").offset;
   uniform_offsets_[NormalMatrix] = uniforms_.at("NormalMatrix").offset;
   uniform_offsets_[Resolution] = uniforms_.at("resolution").offset;
   uniform_offsets_[Time] = uniforms_.at("time").offset;
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

inline void SharedUniforms::setUniform(const Uniform uniform, const glm::mat4& value) {
   subData(uniform_offsets_[uniform], sizeof(value), &value[0]);
}

inline void SharedUniforms::setUniform(const Uniform uniform, const glm::mat3& value) {
   subData(uniform_offsets_[uniform], sizeof(value), &value[0]);
}

inline void SharedUniforms::setUniform(const Uniform uniform, const glm::vec2& value) {
   subData(uniform_offsets_[uniform], sizeof(value), &value[0]);
}

inline void SharedUniforms::setUniform(const Uniform uniform, const GLfloat& value) {
   subData(uniform_offsets_[uniform], sizeof(value), &value);
}

inline g3::GLsizeiptr SharedUniforms::getSize() const {
   return ub_size_;
}

inline void SharedUniforms::bindTo(const ProgramPtr& program) const {
   GLuint index = program->getUniformBlockIndex(uniform_block_name.c_str());
   if(index == GL_INVALID_INDEX) {
      return;
   }
   program->uniformBlockBinding(index, getBindingPoint());
}

#endif /* G3_SHAREDUNIFORMS_HPP_ */
