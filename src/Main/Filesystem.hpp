#ifndef G3TEST_FILESYSTEM_HPP_
#define G3TEST_FILESYSTEM_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace ResourceManager {
   using std::vector;
   using std::string;
   using boost::filesystem::path;
   
   vector<path> findDataPaths();
   string findImageFile(const string& filename);
   string findShaderFile(const string& filename);
   vector<char> readIntoVector(const string& filename);

   //static const vector<string> data_paths;
}

#endif /* G3TEST_FILESYSTEM_HPP_ */
