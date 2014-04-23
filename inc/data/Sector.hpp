#ifndef __SECTOR_HPP__
#define __SECTOR_HPP__

#include <string>

namespace yafic {

  class Sector {
  public:

    Sector(const std::string& _name);

    virtual ~Sector();

    std::string getName() const;

  protected:

  private:
    std::string m_name;
  };

}

#endif
