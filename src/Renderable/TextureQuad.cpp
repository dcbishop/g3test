#include "TextureQuad.hpp"

#include "../Main/Globals.hpp"
#include "../Main/ResourceManager.hpp"

bool TextureQuad::isInitilized_ = false;
unsigned int TextureQuad::refs_ = 0;

VertexArrayPtr TextureQuad::array_;
BufferPtr TextureQuad::buffer_;
ProgramPtr TextureQuad::program_; 

TextureQuad::TextureQuad() {
   if(!isInitilized_) {
      init_();
   }

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
       1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
      -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
       1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
       1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
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

   ResourceManager& rm = globals.getResourceManager();
   program_ = rm.getVFProgram("FlatTexture.vert", "FlatTexture.frag");
   
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
   static GLuint texture_loc = program_->getUniformLocation("sampler0");
   glUniform1i(texture_loc, 0);
   array_->bind();
   glDrawArrays(GL_TRIANGLES, 0, 6);
   array_->unbind();
}
