#ifndef __YAHOO_CONFIG_HPP__
#define __YAHOO_CONFIG_HPP__

#include <ctime>
#include <string>

namespace yafic {
  
  class yahoo_config {
  public:

    static const std::string YQL_HOST;

    static const std::string JSON_GET_ALL_SECTORS;    

    static const std::string XML_GET_ALL_SECTORS;

    static const std::string XML_GET_INDUSTRY_PREFIX;

    static const std::string XML_GET_INDUSTRY_SUFFIX;

    static const std::string XML_GET_HISTO_DATA_SUFFIX;

    static const std::string XML_GET_HISTO_DATA_PREFIX;

    static const std::string START_DATE_CLAUSE;

    static const std::string END_DATE_CLAUSE;

    static std::string getHistoDataRequest(const std::string& _symbol,
					   const std::tm& _startDate,
					   const std::tm& _endDate);

    static std::string getIndustryRequest(const std::string& _id);
  };

}

#endif
