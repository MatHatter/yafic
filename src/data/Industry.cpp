#include "data/Industry.hpp"

namespace yafic {

  Industry::Industry(const int _id, const std::string& _name, 
		     const Sector& _sector) :
    m_id(_id),
    m_name(_name),
    m_sector(_sector) {
  }

  int Industry::getId() const {
    return m_id;
  }
  
  std::string Industry::getName() const {
    return m_name;
  }
  
  const Sector& Industry::getSector() const {
    return m_sector;
  }

}
