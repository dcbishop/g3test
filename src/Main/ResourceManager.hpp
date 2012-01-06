#ifndef G3TEST_RESOURCEMANAGER_HPP_
#define G3TEST_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <tuple> 
#include <boost/filesystem.hpp>

#include "../OpenGL/Program.hpp"
#include "../OpenGL/Shader.hpp"

using std::vector;
using std::shared_ptr;
using std::unordered_map;
using boost::filesystem::path;

typedef unordered_map<std::string, ShaderPtr> ShaderMap;
typedef unordered_map<std::string, ProgramPtr> ProgramMap;

class ResourceManager {   
   public:
      ResourceManager();

      ProgramPtr getVFProgram(const std::string& vertfile, const std::string& fragfile);
      ShaderPtr getShader(const std::string& filename, const Shader::Type& type);
      ShaderPtr getVertexShader(const std::string& filename);
      ShaderPtr getFragmentShader(const std::string& filename);

      ProgramPtr getShaderProgram(const std::string& filename);

   private:
      std::vector<path> findDataPaths_();
      path findImageFile_(const path& filename);
      path findShaderFile_(const path& filename);
      std::vector<char> readIntoVector_(const path& filename);

      ShaderPtr loadShader_(const path& filename, const Shader::Type& type);

      ShaderMap shaders_;
      ProgramMap programs_;

      std::vector<path> hardcoded_data_paths;
      std::vector<path> data_paths_;
};

typedef shared_ptr<ResourceManager> ResourceManagerPtr;

#endif /* G3TEST_RESOURCEMANAGER_HPP_ */
