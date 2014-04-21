#include "data/Sector.hpp"

namespace yafic {

  Sector::Sector(const std::string& _name) : 
    m_name(_name) {
  }

  std::string Sector::getName() const {
    return m_name;
  }

}
