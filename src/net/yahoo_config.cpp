#include "net/yahoo_config.hpp"

#include <sstream>

namespace yafic {

  const std::string yahoo_config::YQL_HOST = "query.yahooapis.com";

  const std::string yahoo_config::JSON_GET_ALL_SECTORS = 
    "/v1/public/yql?q=Select%20*%20From%20yahoo.finance.sectors&format=json&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback=";

  const std::string yahoo_config::XML_GET_ALL_SECTORS = 
    "/v1/public/yql?q=Select%20*%20From%20yahoo.finance.sectors&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";

  const std::string yahoo_config::XML_GET_INDUSTRY_PREFIX = 
    "/v1/public/yql?q=select%20*%20from%20yahoo.finance.industry%20where%20id%3D%22";

  const std::string yahoo_config::XML_GET_INDUSTRY_SUFFIX = 
    "%22&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";

  // Historical data
  const std::string yahoo_config::XML_GET_HISTO_DATA_PREFIX = 
    "/v1/public/yql?q=select%20*%20from%20yahoo.finance.historicaldata%20where%20symbol%20%3D%20%22"; 

  const std::string yahoo_config::XML_GET_HISTO_DATA_SUFFIX = 
    "%22&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";

  const std::string yahoo_config::START_DATE_CLAUSE = 
    "%22%20and%20startDate%20%3D%20%22";

  const std::string yahoo_config::END_DATE_CLAUSE = 
    "%22%20and%20endDate%20%3D%20%22";

  /*
  "SGO.PA";
  "%22%20and%20startDate%20%3D%20%22";
  "2014-04-20";
  "%22%20and%20endDate%20%3D%20%22";
  "2014-04-23";
  */

  std::string 
  yahoo_config::getHistoDataRequest(const std::string& _symbol,
				     const std::tm& _startDate,
				     const std::tm& _endDate) {

    // lambda to format date
    auto format_date = [](const std::tm& _date) {
      std::stringstream ss;
      ss << (1900+_date.tm_year) << "-" <<
      (1+_date.tm_mon) << "-" <<
      _date.tm_mday;
      return ss.str();
    };
    std::stringstream ss;
    ss << XML_GET_HISTO_DATA_PREFIX <<
      _symbol <<   
      START_DATE_CLAUSE <<
      format_date(_startDate) <<
      END_DATE_CLAUSE <<
      format_date(_endDate) <<
      XML_GET_HISTO_DATA_SUFFIX;
    return ss.str();
  }

}
