#include "data/xml_parser.hpp"

#include <climits>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/foreach.hpp>

#include "data/Sector.hpp"
#include "data/Industry.hpp"
#include "data/Stock.hpp"
#include "data/HistoData.hpp"

namespace yafic {

  const std::string xml_parser::INDUSTRY_ELT  = "industry";

  const std::string xml_parser::COMPANY_ELT   = "company";

  const std::string xml_parser::QUOTE_ELT     = "quote";

  const std::string xml_parser::DATE_ELT     = "Date";

  const std::string xml_parser::OPEN_ELT      = "Open";

  const std::string xml_parser::HIGH_ELT      = "High";

  const std::string xml_parser::LOW_ELT       = "Low";

  const std::string xml_parser::CLOSE_ELT     = "Close";

  const std::string xml_parser::VOLUME_ELT    = "Volume";

  const std::string xml_parser::ADJ_CLOSE_ELT = "Adj_Close";


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

  bool xml_parser::parse_histo_data(boost::property_tree::ptree& _ptree,
				    const std::string& _symbol,
				    HistoMap& _histoData) {
    using boost::property_tree::ptree;
    using namespace boost::gregorian;
    std::cout << "Start parsing ... " << std::endl;
    BOOST_FOREACH(ptree::value_type& v,
		  _ptree.get_child("query.results")) {
      if (v.first != QUOTE_ELT) {
	continue;
      }
      std::string companySymbol = 
	v.second.get<std::string>("<xmlattr>.Symbol", NOT_FOUND);
      if (companySymbol != _symbol) {
	std::cout << "Warning - found another symbol " << companySymbol <<
	  std::endl;
	continue;
      }
      decimal open = 0, high = 0, low = 0, close = 0, volume = 0, adjClose = 0;
      date quoteDate;
      BOOST_FOREACH(ptree::value_type& quote_node, v.second.get_child("")) {
	if (quote_node.first == OPEN_ELT) {
	  open = std::stod(quote_node.second.data());
	}
	else if (quote_node.first == HIGH_ELT) {
	  high = std::stod(quote_node.second.data());
	}
	else if (quote_node.first == LOW_ELT) {
	  low = std::stod(quote_node.second.data());
	}
	else if (quote_node.first == CLOSE_ELT) {
	  close = std::stod(quote_node.second.data());
	}
	else if (quote_node.first == VOLUME_ELT) {
	  volume = std::stod(quote_node.second.data());
	}
	else if (quote_node.first == ADJ_CLOSE_ELT) {
	  adjClose = std::stod(quote_node.second.data());
	}
	else if (quote_node.first == DATE_ELT) {
	  quoteDate = from_simple_string(quote_node.second.data());
	}
      }
      if (! quoteDate.is_special()) {
	HistoData hd(quoteDate);
	hd.setOpen(open);
	hd.setHigh(high);
	hd.setLow(low);
	hd.setClose(close);
	hd.setVolume(volume);
	hd.setAdjClose(adjClose);
	_histoData[quoteDate] = hd;
      }
    }
    std::cout << " ... done" << std::endl;
    return true;
  }


}
