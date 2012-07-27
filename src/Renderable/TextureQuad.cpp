#include "TextureQuad.hpp"

using namespace dglw;

#include "../Main/Globals.hpp"
#include "../Main/ResourceManager.hpp"

bool TextureQuad::isInitilized_ = false;
unsigned int TextureQuad::refs_ = 0;

VertexArrayPtr TextureQuad::array_;
BufferPtr TextureQuad::buffer_;

TextureQuad::TextureQuad() {
   if(!isInitilized_) {
      init_();
   }

   ResourceManager& rm = globals.getResourceManager();
   setProgram(rm.getVFProgram("FlatTexture.vert", "FlatTexture.frag"));

   refs_++;

   logGLError();
}

TextureQuad::~TextureQuad() {
   refs_ --;
   if(refs_ == 0) {
      deinit_();
   }
}

struct G3vec3 {
  GLfloat x, y, z; 
};

void TextureQuad::init_() {
   std::vector<float> vertices {
      -1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 
      -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
       1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
      -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
       1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
       1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
   };
   
   array_ = VertexArrayPtr(new VertexArray);
   buffer_ = BufferPtr(new Buffer);

   array_->bind();
   buffer_->bind();
   buffer_->data(vertices.size()*sizeof(G3vec3), &vertices[0]);
   glVertexAttribPointer(AttributeIndex::Vertex, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, 0);
   glVertexAttribPointer(AttributeIndex::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (char*)(sizeof(GLfloat)*3));
   glVertexAttribPointer(AttributeIndex::MultiTextCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (char*)((sizeof(GLfloat)*3)*2));
   glEnableVertexAttribArray(AttributeIndex::Vertex);
   glEnableVertexAttribArray(AttributeIndex::Normal);
   glEnableVertexAttribArray(AttributeIndex::MultiTextCoord0);

   isInitilized_ = true; 
}

void TextureQuad::deinit_() {
   isInitilized_ = false;
   array_->bind();
   buffer_->bind();
   glDisableVertexAttribArray(AttributeIndex::Vertex);
   glDisableVertexAttribArray(AttributeIndex::Normal);
   glDisableVertexAttribArray(AttributeIndex::MultiTextCoord0);
   buffer_->unbind();
   array_->unbind();
   program_ = ProgramPtr();
   array_ = VertexArrayPtr();
   buffer_ = BufferPtr();
}

void TextureQuad::render() {
   program_->use();
   glUniform1i(texture_loc_, 0);
   glUniform1f(time_loc_, globals.getGametime());
   array_->bind();
   glDrawArrays(GL_TRIANGLES, 0, 6);
   array_->unbind();
}

void TextureQuad::setProgram(const ProgramPtr& program) {
   program_ = program;
   texture_loc_ = program_->getUniformLocation("sampler0");
   time_loc_ = program_->getUniformLocation("time");
}
