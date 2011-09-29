#ifndef G3TEST_FILESYSTEM_HPP_
#define G3TEST_FILESYSTEM_HPP_

#include <iostream>
#include <string>
#include <vector>

std::string findImageFile(const std::string& filename);
std::vector<char> readIntoVector(const std::string& filename);

#endif /* G3TEST_FILESYSTEM_HPP_ */
