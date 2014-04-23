#ifndef __HTTP_HELPER_HPP__
#define __HTTP_HELPER_HPP__

#include <string>

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

namespace yafic {

  class http_helper {
  public:
    
    static int
    do_request(const std::string& _server,
	       const std::string& _path,
	       boost::asio::streambuf& _response);

    static int 
    do_request(const std::string& _server,
	       const std::string& _path,
	       boost::property_tree::ptree& _ptree);

  protected:

  private:
    http_helper() { }
  };

}

#endif
