#ifndef __YAHOO_FINANCE_HPP__
#define __YAHOO_FINANCE_HPP__

#include <map>
#include <memory>
#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "data/yafic_types.hpp"

namespace yafic {

  class Sector;
  class Industry;
  class Stock;
  class HistoData;

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

    static bool
    load_histodata(const std::vector<std::string>& _symbols,
		   const boost::gregorian::date& _start,
		   const boost::gregorian::date& _end,
		   yfContainer<HistoMap>& _histoData);

  protected:


  private:


  };

}

#endif 
