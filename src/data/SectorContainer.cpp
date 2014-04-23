#include "data/SectorContainer.hpp"

#include <iostream>

namespace yafic {

  SectorContainer::SectorContainer() {
  }

  SectorContainer::~SectorContainer() {
  }

  bool SectorContainer::addSector(const std::string& _name) {
    if (m_sector.find(_name) == m_sector.end()) {
      m_sector[_name] = std::make_shared<Sector>(_name);
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
	std::make_shared<Industry>(_industryId, _industryName, *m_sector[_sectorName]);
    }
    return false;
  }

  const std::map<std::string, std::shared_ptr<Sector>>& SectorContainer::getSectors() const {
    return m_sector;
  }

  const std::map<int, std::shared_ptr<Industry>>& 
    SectorContainer::getIndustry() const {
    return m_industry;
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

