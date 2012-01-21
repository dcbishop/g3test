#include "Globals.hpp"

#include "ResourceManager.hpp"

Globals globals;

#ifndef BUILD_DATE_
#define BUILD_DATE_ "UNKNOWN"
#endif /* BUILD_DATE_ */
#ifndef GIT_VERSION_
#define GIT_VERSION_ "UNKNOWN"
#endif /* GIT_VERSION_ */
#ifndef GIT_SHA1_
#define GIT_SHA1_ "UNKNOWN"
#endif /* GIT_SHA1_ */
#ifndef BUILD_TYPE_
#define BUILD_TYPE_ "UNKNOWN"
#endif /* BUILD_TYPE_ */

const std::string Globals::build_date_ = BUILD_DATE_;
const std::string Globals::git_version_ = GIT_VERSION_;
const std::string Globals::git_sha1_ = GIT_SHA1_;
const std::string Globals::build_type_ = BUILD_TYPE_;
ResourceManager Globals::rm_;
float Globals::game_time_;

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

const float& Globals::getGametime() const {
   return game_time_;
}

const void Globals::setGametime(const float& game_time) {
   game_time_ = game_time;
}
