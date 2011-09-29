#ifndef G3TEST_GLOBALS_HPP_
#define G3TEST_GLOBALS_HPP_

#include <string>
using namespace std;

class Globals {
   public:
      const string& getBuildDate() const {
         return build_date_;
      }
      const string& getGitVersion() const {
         return git_version_;
      }
      const string& getGitSHA1() const {
         return git_sha1_;
      }

   private:
      static const string build_date_;
      static const string git_version_;
      static const string git_sha1_;
};

extern Globals g;

#endif /* G3TEST_GLOBALS_HPP_ */
