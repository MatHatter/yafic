#ifndef __YAHOO_FINANCE_HPP__
#define __YAHOO_FINANCE_HPP__

#include <map>
#include <memory>
#include <string>

#include "data/yafic_types.hpp"

namespace yafic {

  class Sector;
  class Industry;
  class Stock;

  class yahoo_finance {

  public:

    static bool 
    load_industries(yfContainer<Sector>& _sectors, 
		    yfContainer<Industry>& _industries,
		    bool _force_download = false);
			     
    static bool
    load_stocks(yfContainer<Industry>& _industries,
		yfContainer<Stock>& _stocks,
		bool _force_download = false);

  protected:


  private:


  };

}

#endif 
