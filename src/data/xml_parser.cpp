#include "data/xml_parser.hpp"

#include <climits>

#include <boost/foreach.hpp>

#include "data/Sector.hpp"
#include "data/Industry.hpp"
#include "data/Stock.hpp"

namespace yafic {

  const std::string xml_parser::INDUSTRY_ELT = "industry";

  const std::string xml_parser::COMPANY_ELT = "company";

  bool xml_parser::parse_industries(boost::property_tree::ptree& _ptree,
				 yfContainer<Sector>& _sectors,
				 yfContainer<Industry>& _industries) {
    using boost::property_tree::ptree;
    BOOST_FOREACH(ptree::value_type& node, _ptree.get_child("query.results")) {
      std::string sectorName = 
	node.second.get<std::string>("<xmlattr>.name", NOT_FOUND);
      if (sectorName == NOT_FOUND) {
	continue;
      }
      std::shared_ptr<Sector> sectorPtr = std::make_shared<Sector>(sectorName);
      _sectors[sectorName] = sectorPtr;
      BOOST_FOREACH(ptree::value_type& ind_node, node.second.get_child("")) {
	if (ind_node.first == INDUSTRY_ELT) {
	  std::string industryName = 
	    ind_node.second.get<std::string>("<xmlattr>.name", NOT_FOUND);
	  if (industryName == NOT_FOUND) {
	    continue;
	  }
	  int industryId = 
	    ind_node.second.get<int>("<xmlattr>.id", INT_MIN);
	  _industries[std::to_string(industryId)] =
	    std::make_shared<Industry>(industryId, industryName, *sectorPtr);
	}
      }
    }
    return true;
  }

  bool xml_parser::parse_stocks(boost::property_tree::ptree& _ptree,
				const std::shared_ptr<Industry>& _industry,
				yfContainer<Stock>& _stocks) {
    using boost::property_tree::ptree;
    BOOST_FOREACH(ptree::value_type& v,
		  _ptree.get_child("query.results")) {
      std::string industryName = 
	v.second.get<std::string>("<xmlattr>.name", NOT_FOUND);
      std::cout << industryName << " / " << _industry->getName() << std::endl;
      if (industryName == NOT_FOUND) {
	continue;
      }
      BOOST_FOREACH(ptree::value_type& company_node,
		    v.second.get_child("")) {
	if (company_node.first == COMPANY_ELT) {
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
	  _stocks[companySymbol] = 
	    std::make_shared<Stock>(companyName, companySymbol);
	}
      }
    }
    return true;
  }

  bool xml_parser::parse_histo_data(boost::property_tree::ptree& _ptree) {
    return true;
  }


}
