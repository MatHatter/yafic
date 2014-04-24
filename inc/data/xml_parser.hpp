#ifndef __XML_PARSER_HPP__
#define __XML_PARSER_HPP__

#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "data/yafic_types.hpp"

namespace yafic {

  class Sector;
  class Industry;
  class Stock;

  class xml_parser {

  public:

    static const std::string INDUSTRY_ELT;

    static const std::string COMPANY_ELT;

    static const std::string QUOTE_ELT;

    static const std::string DATE_ELT;

    static const std::string OPEN_ELT;

    static const std::string HIGH_ELT;

    static const std::string LOW_ELT;

    static const std::string CLOSE_ELT;

    static const std::string VOLUME_ELT;

    static const std::string ADJ_CLOSE_ELT;

    static bool 
    parse_industries(boost::property_tree::ptree& _ptree,
		     yfContainer<Sector>& _sectors,
		     yfContainer<Industry>& _industries);

    static bool 
    parse_stocks(boost::property_tree::ptree& _ptree,
		 const std::shared_ptr<Industry>& _industry,
		 yfContainer<Stock>& _stocks);

    static bool 
    parse_histo_data(boost::property_tree::ptree& _ptree,
		     const std::string& _symbol,
		     HistoMap& _histoData);

  };

}

#endif
