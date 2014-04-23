#ifndef __SECTORCONTAINER_HPP__
#define __SECTORCONTAINER_HPP__

#include <string>
#include <map>
#include <memory>

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

    const std::map<std::string, std::shared_ptr<Sector>>& getSectors() const;

    const std::map<int, std::shared_ptr<Industry>>& getIndustry() const;

    void print();


  protected:


  private:
    std::map<std::string, std::shared_ptr<Sector>> m_sector;
    std::map<int, std::shared_ptr<Industry>> m_industry;
  };

}

#endif
