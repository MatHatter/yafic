#ifndef __XML_PARSER_HPP__
#define __XML_PARSER_HPP__

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

    static bool parse_industries(boost::property_tree::ptree& _ptree,
				 yfContainer<Sector>& _sectors,
				 yfContainer<Industry>& _industries);

    static bool parse_stocks(boost::property_tree::ptree& _ptree,
			     const yfContainer<Industry> _industries,
			     yfContainer<Stock>& _stocks);

    static bool parse_histo_data(boost::property_tree::ptree& _ptree);

  };

}

#endif
