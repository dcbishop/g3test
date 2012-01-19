#ifndef G3_SHADER_HPP_
#define G3_SHADER_HPP_

#include "OpenGL.hpp"
#include <memory>

class Texture {
   public:
      enum Target: GLenum {
         Texture2D            = GL_TEXTURE_2D,
         ProxyTexture2D       = GL_PROXY_TEXTURE_2D,
         Texture1DArray       = GL_TEXTURE_1D_ARRAY,
         ProxyTexture1DArray  = GL_PROXY_TEXTURE_1D_ARRAY,
         Rectangle            = GL_TEXTURE_RECTANGLE,
         ProxyRectangle       = GL_PROXY_TEXTURE_RECTANGLE,
         CubeMapPositiveX     = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
         CubeMapNegativeX     = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
         CubeMapPositiveY     = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
         CubeMapNegativeY     = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
         CubeMapPositiveZ     = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
         CubeMapNegativeZ     = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
         ProxyCubeMap         = GL_PROXY_TEXTURE_CUBE_MAP
      };

      enum Parameter: GLenum {
         MinFilter      = GL_TEXTURE_MIN_FILTER,
         MagFilter      = GL_TEXTURE_MAG_FILTER,
         MinLOD         = GL_TEXTURE_MIN_LOD,
         MaxLOD         = GL_TEXTURE_MAX_LOD,
         BaseLevel      = GL_TEXTURE_BASE_LEVEL,
         MaxLevel       = GL_TEXTURE_MAX_LEVEL,
         WrapS          = GL_TEXTURE_WRAP_S,
         WrapT          = GL_TEXTURE_WRAP_T,
         WrapR          = GL_TEXTURE_WRAP_R,
         Priority       = GL_TEXTURE_PRIORITY,
         CompareMode    = GL_TEXTURE_COMPARE_MODE,
         CompareFunc    = GL_TEXTURE_COMPARE_FUNC,
         DepthMode      = GL_DEPTH_TEXTURE_MODE,
         GenerateMipmap = GL_GENERATE_MIPMAP
      };
      
      enum Format: GLenum {
         Red   = GL_RED,
         RG    = GL_RG,
         RGB   = GL_RGB,
         BGR   = GL_BGR,
         RGBA  = GL_RGBA,
         BGRA  = GL_BGRA
      };
      
      enum Type: GLenum {
         UnsignedByte               = GL_UNSIGNED_BYTE,
         Byte                       = GL_BYTE,
         UnsignedShort              = GL_UNSIGNED_SHORT,
         Short                      = GL_SHORT,
         UnsignedInt                = GL_UNSIGNED_INT,
         Int                        = GL_INT,
         Float                      = GL_FLOAT,
         UnsignedByte_3_3_2         = GL_UNSIGNED_BYTE_3_3_2,
         UnsignedByte_2_3_3_Rev     = GL_UNSIGNED_BYTE_2_3_3_REV,
         UnsignedShort_5_6_5        = GL_UNSIGNED_SHORT_5_6_5,
         UnsignedShort_5_6_5_Rev    = GL_UNSIGNED_SHORT_5_6_5_REV,
         UnsignedShort_4_4_4_4      = GL_UNSIGNED_SHORT_4_4_4_4,
         UnsignedShort_4_4_4_4_Rev  = GL_UNSIGNED_SHORT_4_4_4_4_REV,
         UnsignedShort_5_5_5_1      = GL_UNSIGNED_SHORT_5_5_5_1,
         UnsignedShort_1_5_5_5_Rev  = GL_UNSIGNED_SHORT_1_5_5_5_REV,
         UnsignedShort_8_8_8_8      = GL_UNSIGNED_INT_8_8_8_8,
         UnsignedShort_8_8_8_8_Rev  = GL_UNSIGNED_INT_8_8_8_8_REV,
         UnsignedInt_10_10_10_2     = GL_UNSIGNED_INT_10_10_10_2,
         UnsignedInt_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV
      };

      Texture();
      ~Texture();
      void bind(const Target target);
      GLuint getTextureId() const;
      void parameter(const Parameter pname, const GLint& param);
      void parameter(const Target target, const Parameter pname, const GLint& param);
      void parameter(const Parameter pname, const GLfloat& param);
      void parameter(const Target target, const Parameter pname, const GLfloat& param);
      static void activeTexture(GLenum texture);

      void image2D(const Target target, const GLint level,
         const g3::InternalFormat internalFormat, const GLsizei width,
         const GLsizei height, const GLint border, const Format format,
         const Type type, const GLvoid* data);

      static LookupNames TargetNames;
      static LookupNames ParameterNames;
      static LookupNames FormatNames;
      static LookupNames TypeNames;

   private:
      GLuint texid_;
      Target target_;
      
};
typedef std::shared_ptr<Texture> TexturePtr;

inline Texture::Texture() {
   glGenTextures(1, &texid_);
}

inline Texture::~Texture() {
   glDeleteTextures(1, &texid_);
}

inline GLuint Texture::getTextureId() const {
   return texid_;
}

inline void Texture::bind(const Texture::Target target = Texture::Texture2D) {
   target_ = target;
   glBindTexture(target, getTextureId());
}

inline void Texture::image2D(
   const Target target,
   const GLint level,
   const g3::InternalFormat internalFormat,
   const GLsizei width,
   const GLsizei height,
   const GLint border,
   const Format format,
   const Type type,
   const GLvoid* data = nullptr)
{
   glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
}

inline void Texture::parameter(const Parameter pname, const GLint& param) {
   parameter(target_, pname, param);
}

inline void Texture::parameter(const Target target, const Parameter pname, const GLint& param) {
   glTexParameteri(target, pname, param);
}

inline void Texture::parameter(const Parameter pname, const GLfloat& param) {
   parameter(target_, pname, param);
}

inline void Texture::parameter(const Target target, const Parameter pname, const GLfloat& param) {
   glTexParameteri(target, pname, param);
}

// TODO: Is there a proper way to programtically get the defined
// GL_TEXTURE# from an index number. The actual enums might not be in
// sequential order.
// http://www.opengl.org/registry/api/enum.spec lists the first 30 then
// breaks the sequential range (OpenGL requires 80 minimum).
inline void Texture::activeTexture(GLenum texture) {
   glActiveTexture(texture);
}

#endif /* G3_SHADER_HPP_ */
