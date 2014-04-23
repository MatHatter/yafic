#include "data/Sector.hpp"

#include <iostream>

namespace yafic {

  Sector::Sector(const std::string& _name) : 
    m_name(_name) {
  }

  Sector::~Sector() {
    std::cout << "Sector dtor" << std::endl;
  }

  std::string Sector::getName() const {
    return m_name;
  }

}
