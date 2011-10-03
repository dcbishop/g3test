#include "Filesystem.hpp"

#include "../Debug/console.h"

using namespace boost::filesystem;
using namespace std;

namespace ResourceManager {
   const vector<path> hardcoded_data_paths = {"", "../", "~/.sfmltest/Data", "/usr/local/games/sfmltest", "/usr/shared/sfmltest/", "/usr/shared/games/sfmltest/"};   
   const vector<path> data_paths = findDataPaths();

   vector<path> findDataPaths() {
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

   path findImageFile(const path& filename) {
      path p;

      // Note: C++11 only! Range-based for-loop
      for(const path &check_path : data_paths) {
         p = check_path;
         p /= "Images";
         p /= filename;

         if(exists(p)) {
            return p.string();
         }
      }

      return filename;
   }

   path findShaderFile(const path& filename) {
      path p;

      // Note: C++11 only! Range-based for-loop
      for(const path &check_path : data_paths) {
         p = check_path;
         p /= "Shaders";
         p /= filename;

         if(exists(p)) {
            return p.string();
         }
      }

      return filename;
   }

   vector<char> readIntoVector(const path& filename) {
      ifstream file(filename.c_str());
      if(!file.is_open()) {
         ERROR("Could not open '%s'", filename.c_str());
         throw "Badness!";
      }
      return vector<char>(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
   }
}
