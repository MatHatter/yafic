#ifndef __SECTORCONTAINER_HPP__
#define __SECTORCONTAINER_HPP__

#include <string>
#include <map>

#include "data/Sector.hpp"
#include "data/Industry.hpp"

namespace yafic {

  class SectorContainer {

  public:
    SectorContainer();

    virtual ~SectorContainer();

    bool addSector(const std::string& _name);

    bool addIndustry(const std::string& _sectorName,
		     const int _industryId, const std::string& _industryName);

    void print();

  protected:


  private:
    std::map<std::string, Sector*> m_sector;
    std::map<int, Industry*> m_industry;
  };

}

#endif
