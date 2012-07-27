#ifndef G3TEST_RESOURCEMANAGER_HPP_
#define G3TEST_RESOURCEMANAGER_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <tuple> 
#include <boost/filesystem.hpp>

#include <dglw/dglw.hpp>

typedef std::unordered_map<std::string, dglw::ShaderPtr> ShaderMap;
typedef std::unordered_map<std::string, dglw::ProgramPtr> ProgramMap;

class ResourceManager {   
   public:
      ResourceManager();

      dglw::ProgramPtr getVFProgram(const std::string& vertfile, const std::string& fragfile);
      dglw::ShaderPtr getShader(const std::string& filename, const dglw::Shader::Type& type);
      dglw::ShaderPtr getVertexShader(const std::string& filename);
      dglw::ShaderPtr getFragmentShader(const std::string& filename);

      dglw::ProgramPtr getShaderProgram(const std::string& filename);

   private:
      std::vector<boost::filesystem::path> findDataPaths_();
      boost::filesystem::path findImageFile_(const boost::filesystem::path& filename);
      boost::filesystem::path findShaderFile_(const boost::filesystem::path& filename);
      std::vector<char> readIntoVector_(const boost::filesystem::path& filename);

      dglw::ShaderPtr loadShader_(const boost::filesystem::path& filename, const dglw::Shader::Type& type);

      ShaderMap shaders_;
      ProgramMap programs_;

      std::vector<boost::filesystem::path> hardcoded_data_paths;
      std::vector<boost::filesystem::path> data_paths_;
};

typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;

#endif /* G3TEST_RESOURCEMANAGER_HPP_ */
