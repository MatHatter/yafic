#ifndef __YAFIC_TYPES_HPP__
#define __YAFIC_TYPES_HPP__

#include <map>
#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>


namespace yafic {

  class HistoData;

  template<typename T, typename R = std::string>
  using yfContainer = std::map<R, std::shared_ptr<T>>;

  const std::string NOT_FOUND;

  typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<20> > decimal;

  using HistoMap = std::map<boost::gregorian::date, HistoData>;
}

#endif
