#ifndef __YAFIC_TYPES_HPP__
#define __YAFIC_TYPES_HPP__

#include <map>
#include <string>

namespace yafic {

  template<typename T>
  using yfContainer = std::map<std::string, std::shared_ptr<T>>;

  const std::string NOT_FOUND;

}

#endif
