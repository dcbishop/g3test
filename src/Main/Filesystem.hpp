#ifndef SFMLTEST_FILESYSTEM_HPP_
#define SFMLTEST_FILESYSTEM_HPP_

#include <iostream>
#include <string>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "../Debug/console.h"

const static string data_paths[] = {"./Data", "../Data", "", "../", "~/.sfmltest/Data", "/usr/local/games/sfmltest", "/usr/shared/sfmltest/Data", "/usr/shared/games/sfmltest/Data"};

string findImageFile(const string& filename) {
   path p;

   for(int i = 0; i < sizeof(data_paths) / sizeof(string*); i++) {
      p = data_paths[i];
      p /= "Images";
      p /= filename;

      if(exists(p)) {
         return p.string();
      }
   }

   return "" + filename;
}

#endif /* SFMLTEST_FILESYSTEM_HPP_ */
