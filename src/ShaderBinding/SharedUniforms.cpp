#include "SharedUniforms.hpp"

// These are the names as they appear in the shader. They must be kept
// in sync with the enum in SharedUniforms.cpp and the GLSL uniform
// block code.
LookupNames SharedUniforms::UniformNames {
   { MVMatrix,             "MVMatrix"           },
   { ProjectionMatrix,     "ProjectionMatrix"   },
   { MVPMatrix,            "MVPMatrix"          },
   { NormalMatrix,         "NormalMatrix"       },
   { Resolution,           "resolution"         },
   { Time,                 "time"               }
};

std::string SharedUniforms::uniform_block_name("SharedUniforms");
