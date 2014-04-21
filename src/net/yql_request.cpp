#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "net/http_helper.hpp"
#include "net/yahoo_config.hpp"
#include "data/SectorContainer.hpp"

void parse_industry(boost::property_tree::ptree const& pt, 
		    const std::string& _sector_name,
		    yafic::SectorContainer& _sectorContainer)
{
  using boost::property_tree::ptree;
  ptree::const_iterator end = pt.end();
  for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
    if (it->first == "id") {
      std::string id = it->second.get_value<std::string>();
      auto name_it = pt.find("name");
      if (name_it != pt.not_found()) {
	//	std::cout << "\t" << id << ": " << name_it->second.get_value<std::string>() << std::endl;	
	_sectorContainer.addIndustry(_sector_name,
				     std::stoi(id), 
				     name_it->second.get_value<std::string>());
      }
    }
    parse_industry(it->second, _sector_name, _sectorContainer);
  }
}

int main(int argc, char* argv[]) {
  boost::asio::streambuf response;
  yafic::http_helper::do_request(yafic::yahoo_config::YQL_HOST, 
				 yafic::yahoo_config::JSON_GET_ALL_SECTORS,
				 response);

  std::istream is(&response);
  std::cout << "*****" << std::endl;
  std::string s;
  std::stringstream ss;
  while (is >> s) {
    ss << s;
  }
  boost::property_tree::ptree pt;
  try {
    boost::property_tree::read_json(ss, pt);
  }
  catch (std::exception& e) {
    std::cerr << "Error reading the response" << std::endl;
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }
  
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
}
