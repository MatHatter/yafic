#include <iostream>
#include <string>
#include <climits>
#include <ctime>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <sqlite3.h>

#include "data/SectorContainer.hpp"
#include "data/yafic_types.hpp"
#include "data/SqliteManager.hpp"
#include "net/http_helper.hpp"
#include "net/yafic_net.hpp"
#include "net/yahoo_config.hpp"
#include "net/yahoo_finance.hpp"

const std::string NOT_FOUND = "not found";

void parse_histo_data(boost::asio::streambuf& _response) {
  std::istream is(&_response);
  boost::property_tree::ptree pt;
  try {
    read_xml(is, pt);
  }
  catch (std::exception& e) {
    std::cerr << "Error reading the response" << std::endl;
    std::cerr << "Exception: " << e.what() << std::endl;
    return;
  }
  using boost::property_tree::ptree;
  BOOST_FOREACH(ptree::value_type& v,
		pt.get_child("query.results")) {
    if (v.first != "quote") {
      continue;
    }
    BOOST_FOREACH(ptree::value_type& quote_node,
		v.second.get_child("")) {
      std::cout << quote_node.first << "/" << quote_node.second.data() << std::endl;
    }
  }
}

int old_main(int argc, char* argv[]) {
  using boost::property_tree::ptree;
  ptree pt;
  if (yafic::http_helper::do_request(yafic::yahoo_config::YQL_HOST, 
				     yafic::yahoo_config::XML_GET_ALL_SECTORS,
				     pt)
      != yafic::yafic_net::HTTP_OK) {
    return 1;
  }

  yafic::SectorContainer sectorContainer;
  BOOST_FOREACH(ptree::value_type& v, pt.get_child("query.results")) {
    std::string sectorName = 
      v.second.get<std::string>("<xmlattr>.name", NOT_FOUND);
    std::cout << sectorName << std::endl;
    if (sectorName == NOT_FOUND) {
      continue;
    }
    sectorContainer.addSector(sectorName);
    BOOST_FOREACH(ptree::value_type& ind_node,
		v.second.get_child("")) {
      if (ind_node.first == "industry") {
	std::string industryName = 
	  ind_node.second.get<std::string>("<xmlattr>.name", "ind not found");
	if (industryName == NOT_FOUND) {
	  continue;
	}
	int industryId = 
	  ind_node.second.get<int>("<xmlattr>.id", INT_MIN);
	sectorContainer.addIndustry(sectorName, industryId, industryName);
	std::cout << "\t" << industryName  << " / " << 
	  industryId << std::endl;
      }
    }
  }

  auto industries = sectorContainer.getIndustry();
  for (auto& indIt : industries)  {
    std::cout << indIt.first << std::endl;
    int industryId = indIt.first;
    std::stringstream ss;
    ss << yafic::yahoo_config::XML_GET_INDUSTRY_PREFIX <<
      industryId << yafic::yahoo_config::XML_GET_INDUSTRY_SUFFIX;
    yafic::http_helper::do_request(yafic::yahoo_config::YQL_HOST, 
				   ss.str(), pt);
    BOOST_FOREACH(ptree::value_type& v,
		  pt.get_child("query.results")) {
      std::string industryName = 
	v.second.get<std::string>("<xmlattr>.name", NOT_FOUND);
      std::cout << industryName << std::endl;
      if (industryName == NOT_FOUND) {
	continue;
      }
      BOOST_FOREACH(ptree::value_type& company_node,
		    v.second.get_child("")) {
	if (company_node.first == "company") {
	  std::string companyName = 
	    company_node.second.get<std::string>("<xmlattr>.name", NOT_FOUND);
	  if (companyName == NOT_FOUND) {
	    continue;
	  }
	  std::string companySymbol = 
	    company_node.second.get<std::string>("<xmlattr>.symbol", NOT_FOUND);
	  if (companySymbol == NOT_FOUND) {
	    continue;
	  }
	  std::cout << "\t" << companyName  << " / " << companySymbol 
		    << std::endl;
	}
      }
    }
    std::tm startDate, endDate;
    startDate.tm_year = 114;
    startDate.tm_mon  = 3;
    startDate.tm_mday = 22;
    endDate = startDate;
    endDate.tm_mday -= 4;
    boost::asio::streambuf response;
    yafic::http_helper::do_request(yafic::yahoo_config::YQL_HOST, 
				   yafic::yahoo_config::getHistoDataRequest("SGO.PA", startDate, endDate),
				   response);
    parse_histo_data(response);
    break;
  }
}

int main(int argc, char * argv[]) {
  using namespace yafic;
  yfContainer<Sector> sectors;
  yfContainer<Industry> industries;
  yahoo_finance::load_industries(sectors, industries);
  for (auto& sect : sectors) {
    std::cout << "## " << sect.second->getName() << std::endl;
    for (auto& ind : industries) {
      if (ind.second->getSector().getName() == sect.second->getName()) {
	std::cout << "\t- " << ind.second->getName() << std::endl;
      }
    }
  }
}
