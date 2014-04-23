#include "net/yahoo_finance.hpp"

#include <boost/property_tree/ptree.hpp>

#include "data/xml_parser.hpp"
#include "net/http_helper.hpp"
#include "net/yahoo_config.hpp"
#include "net/yafic_net.hpp"

namespace yafic {

  bool 
  yahoo_finance::load_industries(yfContainer<Sector>& _sectors, 
				 yfContainer<Industry>& _industries,
				 bool _force_download) {
    using boost::property_tree::ptree;
    ptree pt;
    if (yafic::http_helper::do_request(yafic::yahoo_config::YQL_HOST, 
				       yafic::yahoo_config::XML_GET_ALL_SECTORS,
				       pt)
	!= yafic::yafic_net::HTTP_OK) {
      return false;
    }
    if ( ! xml_parser::parse_industries(pt, _sectors, _industries)) {
      return false;
    }
    return true;
  }

  bool
  yahoo_finance::load_stocks(yfContainer<Industry>& _industries,
			     yfContainer<Stock>& _stocks,
			     bool _force_download) {
    return true; 
  }

}
