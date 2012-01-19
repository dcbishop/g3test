#include "OpenGL.hpp"

LookupNames g3::FormatNames = {
   // Base Internal Formats
   // OpenGL 4.2 spec - Table 3.11 - page 212
   { GL_DEPTH_COMPONENT, "GL_DEPTH_COMPONENT" },
   { GL_DEPTH_STENCIL, "GL_DEPTH_STENCIL" },
   { GL_RED, "GL_RED" },
   { GL_RG, "GL_RG" },
   { GL_RGB, "GL_RGB" },
   { GL_RGBA, "GL_RGBA" },

   // Sized Internal Formats
   // OpenGL 4.2 spec - Table 3.12 - page 215
   { GL_R8, "GL_R8" },
   { GL_R8_SNORM, "GL_R8_SNORM" },
   { GL_R16, "GL_R16" },
   { GL_R16_SNORM, "GL_R16_SNORM" },
   { GL_RG8, "GL_RG8" },
   { GL_RG8_SNORM, "GL_RG8_SNORM" },
   { GL_RG16, "GL_RG16" },
   { GL_RG16_SNORM, "GL_RG16_SNORM" },
   { GL_R3_G3_B2, "GL_R3_G3_B2" },
   { GL_RGB4, "GL_RGB4" },
   { GL_RGB5, "GL_RGB5" },
   { GL_RGB8, "GL_RGB8" },
   { GL_RGB8_SNORM, "GL_RGB8_SNORM" },
   { GL_RGB10, "GL_RGB10" },
   { GL_RGB12, "GL_RGB12" },
   { GL_RGB16_SNORM, "GL_RGB16_SNORM" },
   { GL_RGBA2, "GL_RGBA2" },
   { GL_RGBA4, "GL_RGBA4" },
   { GL_RGB5_A1, "GL_RGB5_A1" },
   { GL_RGBA8, "GL_RGBA8" },
   { GL_RGBA8_SNORM, "GL_RGBA8_SNORM" },
   { GL_RGB10_A2, "GL_RGB10_A2" },
   { GL_RGB10_A2UI, "GL_RGB10_A2UI" },
   { GL_RGBA12, "GL_RGBA12" },
   { GL_RGBA16, "GL_RGBA16" },
   { GL_SRGB8, "GL_SRGB8" },
   { GL_SRGB8_ALPHA8, "GL_SRGB8_ALPHA8" },
   { GL_R16F, "GL_R16F" },
   { GL_RG16F, "GL_RG16F" },
   { GL_RGB16F, "GL_RGB16F" },
   { GL_RGBA16F, "GL_RGBA16F" },
   { GL_R32F, "GL_R32F" },
   { GL_RG32F, "GL_RG32F" },
   { GL_RGB32F, "GL_RGB32F" },
   { GL_RGBA32F, "GL_RGBA32F" },
   { GL_R11F_G11F_B10F, "GL_R11F_G11F_B10F" },
   { GL_RGB9_E5, "GL_RGB9_E5" },
   { GL_R8I, "GL_R8I" },
   { GL_R8UI, "GL_R8UI" },
   { GL_R16I, "GL_R16I" },
   { GL_R16UI, "GL_R16UI" },
   { GL_R32I, "GL_R32I" },
   { GL_R32UI, "GL_R32UI" },
   { GL_RG8I, "GL_RG8I" },
   { GL_RG8UI, "GL_RG8UI" },
   { GL_RG16I, "GL_RG16I" },
   { GL_RG16UI, "GL_RG16UI" },
   { GL_RG32I, "GL_RG32I" },
   { GL_RG32UI, "GL_RG32UI" },
   { GL_RGB8I, "GL_RGB8I" },
   { GL_RGB8UI, "GL_RGB8UI" },
   { GL_RGB16I, "GL_RGB16I" },
   { GL_RGB16UI, "GL_RGB16UI" },
   { GL_RGB32I, "GL_RGB32I" },
   { GL_RGB32UI, "GL_RGB32UI" },
   { GL_RGBA8I, "GL_RGBA8I" },
   { GL_RGBA8UI, "GL_RGBA8UI" },
   { GL_RGBA16I, "GL_RGBA16I" },
   { GL_RGBA16UI, "GL_RGBA16UI" },
   { GL_RGBA32I, "GL_RGBA32I" },
   { GL_RGBA32UI, "GL_RGBA32UI" },

   // Sized internal depth and stencil formats
   // OpenGL 4.2 spec - Table 3.13 - page 218
   { GL_DEPTH_COMPONENT16, "GL_DEPTH_COMPONENT16" },
   { GL_DEPTH_COMPONENT24, "GL_DEPTH_COMPONENT24" },
   { GL_DEPTH_COMPONENT32, "GL_DEPTH_COMPONENT32" },
   { GL_DEPTH_COMPONENT32F, "GL_DEPTH_COMPONENT32F" },
   { GL_DEPTH24_STENCIL8, "GL_DEPTH24_STENCIL8" },
   { GL_DEPTH32F_STENCIL8, "GL_DEPTH32F_STENCIL8" },

   //{ GL_STENCIL_INDEX, "GL_STENCIL_INDEX" },

   // Generic and specific GL_COMPRESSED internal formats
   // OpenGL 4.2 spec - Table 3.14 - Page 218
   /*{ GL_COMPRESSED_RED, "GL_COMPRESSED_RED" },
   { GL_COMPRESSED_RG, "GL_COMPRESSED_RG" },
   { GL_COMPRESSED_RGB, "GL_COMPRESSED_RGB" },
   { GL_COMPRESSED_RGBA, "GL_COMPRESSED_RGBA" },
   { GL_COMPRESSED_SRGB, "GL_COMPRESSED_SRGB" },
   { GL_COMPRESSED_SRGB_ALPHA, "GL_COMPRESSED_SRGB_ALPHA" },
   { GL_COMPRESSED_RED_RGTC1, "GL_COMPRESSED_RED_RGTC1" },
   { GL_COMPRESSED_SIGNED_RED_RGTC1, "GL_COMPRESSED_SIGNED_RED_RGTC1" },
   { GL_COMPRESSED_RG_RGTC2, "GL_COMPRESSED_RG_RGTC2" },
   { GL_COMPRESSED_SIGNED_RG_RGTC2, "GL_COMPRESSED_SIGNED_RG_RGTC2" },
   { GL_COMPRESSED_RGBA_BPTC_UNORM, "GL_COMPRESSED_RGBA_BPTC_UNORM" },
   { GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM" },
   { GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT" },
   { GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT, "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT" },*/

   // Sized Internal Formats (Render buffers only)
   // OpenGL 4.2 spec - Table 4.10 - page 325
   { GL_STENCIL_INDEX1, "GL_STENCIL_INDEX1" },
   { GL_STENCIL_INDEX4, "GL_STENCIL_INDEX4" },
   { GL_STENCIL_INDEX8, "GL_STENCIL_INDEX8" },
   { GL_STENCIL_INDEX16, "GL_STENCIL_INDEX16" }
};