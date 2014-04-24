#include "net/http_helper.hpp"

#include <iostream>
#include <istream>
#include <ostream>

#include <boost/property_tree/xml_parser.hpp>

#include "net/yafic_net.hpp"

namespace yafic {

  int 
  http_helper::do_request(const std::string& _server,
			  const std::string& _path,
			  boost::asio::streambuf& _response) {
    try {
      boost::asio::io_service io_service;
      boost::asio::ip::tcp::tcp::resolver resolver{io_service};
      boost::asio::ip::tcp::tcp::resolver::query query(_server, "http");
      auto endpoint_it = resolver.resolve(query);
      boost::asio::ip::tcp::tcp::socket socket{io_service};
      boost::asio::connect(socket, endpoint_it);

      boost::asio::streambuf request;
      std::ostream request_stream{&request};
      request_stream << "GET " << _path << " HTTP/1.0\r\n" <<
	"Host: " << _server << "\r\n" <<
	"Accept: */*\r\n" <<
	"Connection: close\r\n\r\n";
      boost::asio::write(socket, request);
    
      ;
      boost::asio::read_until(socket, _response, "\r\n");

      std::istream response_stream{&_response};
      std::string http_version;
      response_stream >> http_version;
      unsigned int status_code;
      response_stream >> status_code;
      std::string status_message;
      getline(response_stream, status_message);
      if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
	std::cout << "Invalid response\n";
	return yafic_net::HTTP_INVALID;
      }
      if (status_code != 200) {
	std::cerr << "Response returned with status code " << 
	  status_code << std::endl;
	return yafic_net::HTTP_STATUS_ERROR;
      }
      boost::asio::read_until(socket, _response, "\r\n\r\n");

      std::string header;
      // std::cout << "-- Header" << std::endl;
      while (getline(response_stream, header) && header != "\r") {
	// std::cout << header << std::endl;
      }
      // std::cout << "--" << std::endl;
      boost::system::error_code error;
      while (boost::asio::read(socket, _response,
			       boost::asio::transfer_at_least(1), error)) {
      }
      if (error != boost::asio::error::eof)
	throw boost::system::system_error(error);
    }
    catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      return yafic_net::HTTP_STATUS_ERROR;
    }
    return yafic_net::HTTP_OK;    
  } // end do_request

  int 
  http_helper::do_request(const std::string& _server,
			  const std::string& _path,
			  boost::property_tree::ptree& _ptree) {
    boost::asio::streambuf response;
    int result = do_request(_server, _path, response);
    if (result != yafic_net::HTTP_OK) {
      return result;
    }
    std::istream is(&response);
    try {
      read_xml(is, _ptree);
    }
    catch (std::exception& e) {
      std::cerr << "Error reading the response" << std::endl;
      std::cerr << "Exception: " << e.what() << std::endl;
      return yafic_net::HTTP_RESPONSE_INVALID;
    }
    return result;
  }

}
