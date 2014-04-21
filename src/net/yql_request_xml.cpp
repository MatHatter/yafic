#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "net/http_helper.hpp"
#include "net/yahoo_config.hpp"
#include "data/SectorContainer.hpp"

int main(int argc, char* argv[]) {
  boost::asio::streambuf response;
  yafic::http_helper::do_request(yafic::yahoo_config::YQL_HOST, 
				 yafic::yahoo_config::XML_GET_ALL_SECTORS,
				 response);

  std::istream is(&response);
  boost::property_tree::ptree pt;
  try {
    read_xml(is, pt);
  }
  catch (std::exception& e) {
    std::cerr << "Error reading the response" << std::endl;
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }
  using boost::property_tree::ptree;
  BOOST_FOREACH(ptree::value_type& v,
		pt.get_child("query.results")) {
    std::cout << v.second.get<std::string>("<xmlattr>.name", "not found") << std::endl;
    BOOST_FOREACH(ptree::value_type& ind_node,
		v.second.get_child("")) {
      if (ind_node.first == "industry") {
	std::cout << "\t" << ind_node.second.get<std::string>("<xmlattr>.name", "ind not found") << std::endl;
      }
    }
  }
/*
  auto it = pt.find("query");
  if (it == pt.not_found()) {
    std::cerr << "Cannot parse json result" << std::endl;
    return 1;
  }
  for (std::string key :  {"results", "sector"}) {
    std::cout << "Looking for " << key << std::endl;
    it = it->second.find(key);
    if (it == pt.not_found()) {
      std::cerr << key << " not found" << std::endl;
      return 1;
    }
  }
  yafic::SectorContainer sectorContainer;
  for (auto& it_sector : it->second) {
    std::string sector_name = it_sector.second.get<std::string>("name");
    std::cout << sector_name << ": " << std::endl;
    sectorContainer.addSector(sector_name);
    auto it_industry = it_sector.second.find("industry");
    if (it_industry == it_sector.second.not_found()) {
      std::cout << "\tNo industry found" << std::endl;
      continue;
    }
    parse_industry(it_industry->second, sector_name, sectorContainer);
  }
  sectorContainer.print();
*/
}
