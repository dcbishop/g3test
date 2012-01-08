#include "Globals.hpp"

#include "ResourceManager.hpp"

Globals globals;

#ifndef _BUILD_DATE
#define _BUILD_DATE "UNKNOWN"
#endif /* _BUILD_DATE */
#ifndef _GIT_VERSION
#define _GIT_VERSION "UNKNOWN"
#endif /* _GIT_VERSION */
#ifndef _GIT_SHA1
#define _GIT_SHA1 "UNKNOWN"
#endif /* _GIT_SHA1 */

const std::string Globals::build_date_ = _BUILD_DATE;
const std::string Globals::git_version_ = _GIT_VERSION;
const std::string Globals::git_sha1_ = _GIT_SHA1;
const std::string Globals::build_type_ = _BUILD_TYPE;
ResourceManager Globals::rm_;

Globals g;


const std::string& Globals::getBuildDate() const {
   return build_date_;
}

const std::string& Globals::getGitVersion() const {
   return git_version_;
}

const std::string& Globals::getGitSHA1() const {
   return git_sha1_;
}

const std::string& Globals::getBuildType() const {
   return build_type_;
}

ResourceManager& Globals::getResourceManager() const {
   return rm_;
}
