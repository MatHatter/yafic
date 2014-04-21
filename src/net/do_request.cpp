#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include <boost/asio.hpp>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Starting ..." << endl;
  try {
    string server{argv[1]}, path{argv[2]};
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::tcp::resolver resolver{io_service};
    boost::asio::ip::tcp::tcp::resolver::query query(server, "http");
    auto endpoint_it = resolver.resolve(query);
    boost::asio::ip::tcp::tcp::socket socket{io_service};
    boost::asio::connect(socket, endpoint_it);

    boost::asio::streambuf request;
    ostream request_stream{&request};
    request_stream << "GET " << path << " HTTP/1.0\r\n" <<
      "Host: " << server << "\r\n" <<
      "Accept: */*\r\n" <<
      "Connection: close\r\n\r\n";
    boost::asio::write(socket, request);
    
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    istream response_stream{&response};
    string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    string status_message;
    getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
      std::cout << "Invalid response\n";
      return 1;
    }
    if (status_code != 200) {
      std::cout << "Response returned with status code " << status_code << "\n";
      return 1;
    }
    boost::asio::read_until(socket, response, "\r\n\r\n");

    std::string header;
    cout << "-- Header" << endl;
    while (getline(response_stream, header) && header != "\r") {
      cout << header << endl;
    }
    cout << "*****" << endl;
    if (response.size() > 0) {
      cout << &response;
    }
    cout << "*****" << endl;
    boost::system::error_code error;
    while (boost::asio::read(socket, response,
			     boost::asio::transfer_at_least(1), error))
      std::cout << &response;
    if (error != boost::asio::error::eof)
      throw boost::system::system_error(error);
  }
  catch (...) {
    cerr << "Error" << endl;
    return 1;
  }
}
