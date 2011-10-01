#include "Filesystem.hpp"

#include "../Debug/console.h"

using namespace boost::filesystem;
using namespace std;

namespace ResourceManager {
   static const vector<string> data_paths = {"./Data", "../Data", "", "../", "~/.sfmltest/Data", "/usr/local/games/sfmltest", "/usr/shared/sfmltest/Data", "/usr/shared/games/sfmltest/Data"};   

   vector<path> findDataPaths() {
      path p;

      vector<path> valid_paths;

      // Note: C++11 only! Range-based for-loop
      for(const string &check_path : data_paths) {
         p = check_path;
         p /= "Data";

         if(exists(p) && is_directory(p)) {
            valid_paths.push_back(check_path);
         }
      }

      return valid_paths;
   }

   string findImageFile(const string& filename) {
      path p;

      // Note: C++11 only! Range-based for-loop
      for(const string &check_path : data_paths) {
         p = check_path;
         p /= "Images";
         p /= filename;

         if(exists(p)) {
            return p.string();
         }
      }

      return "" + filename;
   }

   string findShaderFile(const string& filename) {
      path p;

      // Note: C++11 only! Range-based for-loop
      for(const string &check_path : data_paths) {
         p = check_path;
         p /= "Shaders";
         p /= filename;

         if(exists(p)) {
            return p.string();
         }
      }

      return "" + filename;
   }

   vector<char> readIntoVector(const string& filename) {
      ifstream file(filename.c_str());
      if(!file.is_open()) {
         ERROR("Could not open '%s'", filename.c_str());
         throw "Badness!";
      }
      return vector<char>(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
   }
}
