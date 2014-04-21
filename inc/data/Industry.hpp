#ifndef __INDUSTRY_HPP__
#define __INDUSTRY_HPP__

#include <string>

#include "Sector.hpp"

namespace yafic {

  class Industry {

  public:

    Industry(const int _id, const std::string& _name, 
	     const Sector& _sector);

    int getId() const;

    std::string getName() const;

    const Sector& getSector() const;

  protected:

  private:
    int m_id;
    std::string m_name;
    const Sector& m_sector;


  };

}

#endif
