#include "ResourceManager.hpp"

#include <fstream>

#include "../Debug/console.h"

using namespace boost::filesystem;
using namespace std;

// [TODO]: Boost won't expand ~ to the home directory. Consider getenv("HOME").
ResourceManager::ResourceManager() {
   DEBUG_M("Initilizing ResourceManager");
   hardcoded_data_paths = {"", "../", "~/.g3test/Data", "/usr/local/games/g3test", "/usr/shared/g3test/", "/usr/shared/games/g3test/"};
   data_paths_ = findDataPaths_();

   if(!hardcoded_data_paths.size() > 0) {
      ERROR("Failed to set list of hardcoded data folder locations.");
   }
   
}

// TODO: Program caching is somewhat simplified. Odd combinations of names could theoretically break it.
// TODO: Need a function to load arbirary number/types of programs. Maybe C++11 Variadic template?
// TODO: If program fails to load, return a fallback default one.
ProgramPtr ResourceManager::getVFProgram(const std::string& vertfile, const std::string& fragfile) {
   std::string joined = vertfile + fragfile;

   ProgramMap::iterator itr = programs_.find(joined);
   if(itr != programs_.end()) {
      return (*itr).second;
   }

   DEBUG_M("Creating Shader Program from \"%s\" and \"%s\"", vertfile.c_str(), fragfile.c_str());
   ProgramPtr program(new Program);

   // Get the vertex shader
   ShaderPtr vertex_shader = getVertexShader(vertfile);
   logGLError();
   vertex_shader->debugLog();

   // Get the fragment shader
   ShaderPtr fragment_shader = getFragmentShader(fragfile);
   logGLError();
   fragment_shader->debugLog();

   // Make a shader program
   program->attach(vertex_shader);
   program->attach(fragment_shader);
   program->link();

   programs_[joined] = program;
   return program;
}

ShaderPtr ResourceManager::getVertexShader(const std::string& filename) {
   return getShader(filename, Shader::Vertex);
}

ShaderPtr ResourceManager::getFragmentShader(const std::string& filename) {
   return getShader(filename, Shader::Fragment);
}

ShaderPtr ResourceManager::getShader(const std::string& filename, const Shader::Type& type) {
   ShaderMap::iterator itr = shaders_.find(filename);
   if(itr != shaders_.end()) {
      return (*itr).second;
   }

   path fullname = findShaderFile_(filename);
   ShaderPtr shader = loadShader_(fullname, type);
   shaders_[filename] = shader;
   return shader;
}

shared_ptr<Shader> ResourceManager::loadShader_(const path& filename, const Shader::Type& type) {
   auto source = readIntoVector_(filename);
   shared_ptr<Shader> shader(new Shader(type, source));
   shader->compile();
   return shader;
}

vector<path> ResourceManager::findDataPaths_() {
   DEBUG_M("Updating data paths.");
   path p;

   vector<path> valid_paths;

   // Note: C++11 only! Range-based for-loop
   for(const path &check_path : hardcoded_data_paths) {
      p = check_path;
      p /= "Data";

      if(exists(p) && is_directory(p)) {
         valid_paths.push_back(p);
      }
   }

   return valid_paths;
}

path ResourceManager::findImageFile_(const path& filename) {
   path p;

   // Note: C++11 only! Range-based for-loop
   for(const path &check_path : data_paths_) {
      p = check_path;
      p /= "Images";
      p /= filename;

      if(exists(p)) {
         return p.string();
      }
   }

   return filename;
}

path ResourceManager::findShaderFile_(const path& filename) {
   DEBUG_M("Finding \"%s\"", filename.c_str());
   path p;

   // Note: C++11 only! Range-based for-loop
   for(const path &check_path : data_paths_) {
      p = check_path;
      p /= "Shaders";
      p /= filename;

      if(exists(p)) {
         DEBUG_M("Found!");
         return p.string();
      }
   }

   ERROR("Failed to locate file '%s'", filename.c_str());
   return filename;
}

vector<char> ResourceManager::readIntoVector_(const path& filename) {
   ifstream file(filename.c_str());
   if(!file.is_open()) {
      ERROR("Could not open '%s'", filename.c_str());
      throw "Badness!";
   }
   return vector<char>(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
}
