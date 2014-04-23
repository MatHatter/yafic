#include <iostream>
#include <string>
#include <climits>
#include <ctime>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <sqlite3.h>

#include "data/Industry.hpp"
#include "data/Sector.hpp"
#include "net/yahoo_finance.hpp"

int main(int argc, char * argv[]) {
  using namespace yafic;
  yfContainer<Sector> sectors;
  yfContainer<Industry> industries;
  yahoo_finance::load_industries(sectors, industries);
  for (auto& sect : sectors) {
    std::cout << "## " << sect.second->getName() << std::endl;
    for (auto& ind : industries) {
      if (ind.second->getSector().getName() == sect.second->getName()) {
	std::cout << "\t- " << ind.second->getName() << std::endl;
      }
    }
  }
}
