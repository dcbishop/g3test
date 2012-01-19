#include "Texture.hpp"

LookupNames Texture::TargetNames {
   { GL_TEXTURE_1D,                   "GL_TEXTURE_1D"                },
   { GL_TEXTURE_2D,                   "GL_TEXTURE_2D"                },
   { GL_TEXTURE_3D,                   "GL_TEXTURE_3D"                },
   { GL_TEXTURE_1D_ARRAY,             "GL_TEXTURE_1D_ARRAY"          },
   { GL_TEXTURE_2D_ARRAY,             "GL_TEXTURE_2D_ARRAY"          },
   { GL_TEXTURE_RECTANGLE,            "GL_TEXTURE_RECTANGLE"         },
   { GL_TEXTURE_CUBE_MAP,             "GL_TEXTURE_CUBE_MAP"          },
   { GL_TEXTURE_2D_MULTISAMPLE,       "GL_TEXTURE_2D_MULTISAMPLE"    },
   { GL_TEXTURE_2D_MULTISAMPLE_ARRAY, "GL_TEXTURE_2D_MULTISAMPLE_ARRAY"}
};

LookupNames Texture::ParameterNames {
   { GL_TEXTURE_MIN_FILTER,     "GL_TEXTURE_MIN_FILTER"   },
   { GL_TEXTURE_MAG_FILTER,     "GL_TEXTURE_MAG_FILTER"   },
   { GL_TEXTURE_MIN_LOD,        "GL_TEXTURE_MIN_LOD"      },
   { GL_TEXTURE_MAX_LOD,        "GL_TEXTURE_MAX_LOD"      },
   { GL_TEXTURE_BASE_LEVEL,     "GL_TEXTURE_BASE_LEVEL"   },
   { GL_TEXTURE_MAX_LEVEL,      "GL_TEXTURE_MAX_LEVEL"    },
   { GL_TEXTURE_WRAP_S,         "GL_TEXTURE_WRAP_S"       },
   { GL_TEXTURE_WRAP_T,         "GL_TEXTURE_WRAP_T"       },
   { GL_TEXTURE_WRAP_R,         "GL_TEXTURE_WRAP_R"       },
   { GL_TEXTURE_PRIORITY,       "GL_TEXTURE_PRIORITY"     },
   { GL_TEXTURE_COMPARE_MODE,   "GL_TEXTURE_COMPARE_MODE" },
   { GL_TEXTURE_COMPARE_FUNC,   "GL_TEXTURE_COMPARE_FUNC" },
   { GL_DEPTH_TEXTURE_MODE,     "GL_DEPTH_TEXTURE_MODE"   },
   { GL_GENERATE_MIPMAP,        "GL_GENERATE_MIPMAP"      }
};
       
LookupNames Texture::FormatNames {  
   { GL_RED,   "GL_RED"  },
   { GL_RG,    "GL_RG"   },
   { GL_RGB,   "GL_RGB"  },
   { GL_BGR,   "GL_BGR"  },
   { GL_RGBA,  "GL_RGBA" },
   { GL_BGRA,  "GL_BGRA" }
};

LookupNames Texture::TypeNames {
   { GL_UNSIGNED_BYTE,                "GL_UNSIGNED_BYTE"              },
   { GL_BYTE,                         "GL_BYTE"                       },
   { GL_UNSIGNED_SHORT,               "GL_UNSIGNED_SHORT"             },
   { GL_SHORT,                        "GL_SHORT"                      },
   { GL_UNSIGNED_INT,                 "GL_UNSIGNED_INT"               },
   { GL_INT,                          "GL_INT"                        },
   { GL_FLOAT,                        "GL_FLOAT"                      },
   { GL_UNSIGNED_BYTE_3_3_2,          "GL_UNSIGNED_BYTE_3_3_2"        },
   { GL_UNSIGNED_BYTE_2_3_3_REV,      "GL_UNSIGNED_BYTE_2_3_3_REV"    },
   { GL_UNSIGNED_SHORT_5_6_5,         "GL_UNSIGNED_SHORT_5_6_5"       },
   { GL_UNSIGNED_SHORT_5_6_5_REV,     "GL_UNSIGNED_SHORT_5_6_5_REV"   },
   { GL_UNSIGNED_SHORT_4_4_4_4,       "GL_UNSIGNED_SHORT_4_4_4_4"     },
   { GL_UNSIGNED_SHORT_4_4_4_4_REV,   "GL_UNSIGNED_SHORT_4_4_4_4_REV" },
   { GL_UNSIGNED_SHORT_5_5_5_1,       "GL_UNSIGNED_SHORT_5_5_5_1"     },
   { GL_UNSIGNED_SHORT_1_5_5_5_REV,   "GL_UNSIGNED_SHORT_1_5_5_5_REV" },
   { GL_UNSIGNED_INT_8_8_8_8,         "GL_UNSIGNED_INT_8_8_8_8"       },
   { GL_UNSIGNED_INT_8_8_8_8_REV,     "GL_UNSIGNED_INT_8_8_8_8_REV"   },
   { GL_UNSIGNED_INT_10_10_10_2,      "GL_UNSIGNED_INT_10_10_10_2"    },
   { GL_UNSIGNED_INT_2_10_10_10_REV,  "GL_UNSIGNED_INT_2_10_10_10_REV"}
};
