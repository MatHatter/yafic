#include "net/yahoo_config.hpp"

namespace yafic {

  const std::string yahoo_config::YQL_HOST = "query.yahooapis.com";

  const std::string yahoo_config::JSON_GET_ALL_SECTORS = 
    "/v1/public/yql?q=Select%20*%20From%20yahoo.finance.sectors&format=json&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback=";

  const std::string yahoo_config::XML_GET_ALL_SECTORS = 
    "/v1/public/yql?q=Select%20*%20From%20yahoo.finance.sectors&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
}
