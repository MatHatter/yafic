#include "data/SectorContainer.hpp"

#include <iostream>

namespace yafic {

  SectorContainer::SectorContainer() {
  }

  SectorContainer::~SectorContainer() {
    for (auto& it : m_industry) {
      delete it.second;
    }
    m_industry.clear();
    for (auto& it : m_sector) {
      delete it.second;
    }
    m_sector.clear();
  }

  bool SectorContainer::addSector(const std::string& _name) {
    if (m_sector.find(_name) == m_sector.end()) {
      m_sector[_name] = new Sector(_name);
      return true;
    }
    return false;
  }

  bool SectorContainer::addIndustry(const std::string& _sectorName,
				    const int _industryId, 
				    const std::string& _industryName) {
    addSector(_sectorName);
    if (m_industry.find(_industryId) == m_industry.end()) {
      m_industry[_industryId] = 
	new Industry(_industryId, _industryName, *m_sector[_sectorName]);
    }
    return false;
  }

  void SectorContainer::print() {
    for (auto& sec_it : m_sector) {
      std::cout << sec_it.first << std::endl;
      for (auto ind_it : m_industry) {
	if (ind_it.second->getSector().getName() == sec_it.first) {
	  std::cout << "\t" << ind_it.second->getId() << " / " << 
	    ind_it.second->getName() << std::endl;
	}
      }
    }
  }
}

