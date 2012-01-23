#include "Buffer.hpp"

Buffer::Buffer() {
   glGenBuffers(1, &buffer_id_);
   DEBUG_M("Created buffer %d.", buffer_id_);
   logGLError();
   target_ = Array;
   usage_ = StaticDraw;
}

Buffer::~Buffer() {
   DEBUG_M("Deconstructing buffer %d.", buffer_id_);
   glDeleteBuffers(1, &buffer_id_);
   logGLError();
}

LookupNames Buffer::TargetNames = {
   { GL_ARRAY_BUFFER,               "GL_ARRAY_BUFFER"                },
#ifdef GL_ATOMIC_COUNTER_BUFFER
   { GL_ARRAY_BUFFER,               "GL_ATOMIC_COUNTER_BUFFER"       },
#endif
   { GL_COPY_READ_BUFFER,           "GL_COPY_READ_BUFFER"            },
   { GL_COPY_WRITE_BUFFER,          "GL_COPY_WRITE_BUFFER"           },
   { GL_DRAW_INDIRECT_BUFFER,       "GL_DRAW_INDIRECT_BUFFER"        },
   { GL_ELEMENT_ARRAY_BUFFER,       "GL_ELEMENT_ARRAY_BUFFER"        },
   { GL_PIXEL_PACK_BUFFER,          "GL_PIXEL_PACK_BUFFER"           },
   { GL_PIXEL_UNPACK_BUFFER,        "GL_PIXEL_UNPACK_BUFFER"         },
   { GL_TEXTURE_BUFFER,             "GL_TEXTURE_BUFFER"              },
   { GL_TRANSFORM_FEEDBACK_BUFFER,  "GL_TRANSFORM_FEEDBACK_BUFFER"   },
   { GL_UNIFORM_BUFFER,             "GL_UNIFORM_BUFFER"              }
};

LookupNames Buffer::UsageNames = {
   { GL_STATIC_DRAW,    "GL_STATIC_DRAW"  },
   { GL_STATIC_READ,    "GL_STATIC_READ"  },
   { GL_STATIC_COPY,    "GL_STATIC_COPY"  },
   { GL_DYNAMIC_DRAW,   "GL_DYNAMIC_DRAW" },
   { GL_DYNAMIC_READ,   "GL_DYNAMIC_READ" },
   { GL_DYNAMIC_COPY,   "GL_DYNAMIC_COPY" },
   { GL_STREAM_DRAW,    "GL_STREAM_DRAW"  },
   { GL_STREAM_READ,    "GL_STREAM_READ"  },
   { GL_STREAM_COPY,    "GL_STREAM_COPY"  }
};
