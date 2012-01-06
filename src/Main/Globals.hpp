#ifndef G3TEST_GLOBALS_HPP_
#define G3TEST_GLOBALS_HPP_

#include <string>

class ResourceManager;

class Globals {
   public:
      const std::string& getBuildDate() const;
      const std::string& getGitVersion() const;
      const std::string& getGitSHA1() const;
      ResourceManager& getResourceManager() const;

   private:
      static const std::string build_date_;
      static const std::string git_version_;
      static const std::string git_sha1_;
      static ResourceManager rm_;
};

extern Globals globals;

#endif /* G3TEST_GLOBALS_HPP_ */
