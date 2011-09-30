#include "Filesystem.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "../Debug/console.h"

const static string data_paths[] = {"./Data", "../Data", "", "../", "~/.sfmltest/Data", "/usr/local/games/sfmltest", "/usr/shared/sfmltest/Data", "/usr/shared/games/sfmltest/Data"};

std::string findImageFile(const std::string& filename) {
   path p;

   for(int i = 0; i < sizeof(data_paths) / sizeof(string*); ++i) {
      p = data_paths[i];
      p /= "Images";
      p /= filename;

      if(exists(p)) {
         return p.string();
      }
   }

   return "" + filename;
}

std::string findShaderFile(const std::string& filename) {
   path p;

   for(int i = 0; i < sizeof(data_paths) / sizeof(string*); ++i) {
      p = data_paths[i];
      p /= "Shaders";
      p /= filename;

      if(exists(p)) {
         return p.string();
      }
   }

   return "" + filename;
}

std::vector<char> readIntoVector(const std::string& filename) {
   ifstream file(filename.c_str());
   if(!file.is_open()) {
      ERROR("Could not open '%s'", filename.c_str());
      throw "Badness!";
   }
   return vector<char>(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
}
