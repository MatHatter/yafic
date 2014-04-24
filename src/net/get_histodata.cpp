#include <iostream>
#include <string>
#include <climits>
#include <ctime>

#include <boost/date_time/gregorian/gregorian.hpp>

#include "data/Industry.hpp"
#include "data/Sector.hpp"
#include "data/HistoData.hpp"
#include "net/yahoo_finance.hpp"

void usage() {
  std::cout << "Usage :" << std::endl <<
    "\tget_histodata <symbol> <start_date> <end_date>" << std::endl <<
    "Date format is \"yyyy-mm-dd\"" << std::endl;
}

int main(int argc, char * argv[]) {
  using namespace yafic;
  if (argc != 4) {
    usage();
    return 1;
  }
  using namespace boost::gregorian;
  std::string symbol {argv[1]};
  date startDate = day_clock::local_day();
  date endDate;
  try {
    startDate = from_simple_string(argv[2]);
    endDate  = from_simple_string(argv[3]);
  }
  catch (std::exception& e) {
    std::cerr << "Malformed date " << e.what() << std::endl;
    return 1;
  }
  std::cout << startDate << " to " << endDate << std::endl;
  yfContainer<HistoMap> histoData;
  if ( ! yahoo_finance::load_histodata({symbol}, startDate, endDate, histoData)) {
    std::cerr << "Error when retrieving histo data" << std::endl;
  }
  for (auto& symbIt : histoData) {
    std::cout << symbIt.first << std::endl;
    for (auto& dataIt : *symbIt.second) {
      std::cout << "\t" << dataIt.second << std::endl;
    }
  }

}
