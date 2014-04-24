#include "data/HistoData.hpp"

#include <iomanip>

namespace yafic {

  HistoData::HistoData(const boost::gregorian::date& _date) 
    : m_date(_date),
      m_open(0), m_high(0), m_low(0), m_close(0), m_volume(0), m_adjClose(0) {
  }

  HistoData::HistoData() 
    : m_date(),
      m_open(0), m_high(0), m_low(0), m_close(0), m_volume(0), m_adjClose(0) {
  }

  HistoData::~HistoData() {
  }


  void HistoData::setOpen    (const decimal& _value) {
    m_open = _value;
  }

  void HistoData::setHigh    (const decimal& _value) {
    m_high = _value;
  }

  void HistoData::setLow     (const decimal& _value) {
    m_low = _value;
  }

  void HistoData::setClose   (const decimal& _value) {
    m_close = _value;
  }

  void HistoData::setVolume  (const decimal& _value) {
    m_volume = _value;
  }

  void HistoData::setAdjClose(const decimal& _value) {
    m_adjClose = _value;
  }

  
  decimal HistoData::getOpen    () const {
    return m_open;
  }

  decimal HistoData::getHigh    () const {
    return m_high;
  }

  decimal HistoData::getLow     () const {
    return m_low;
  }

  decimal HistoData::getClose   () const {
    return m_close;
  }

  decimal HistoData::getVolume  () const {
    return m_volume;
  }

  decimal HistoData::getAdjClose() const {
    return m_adjClose;
  }

  std::ostream& operator << (std::ostream& _os, const HistoData& _hd) {
    _os.precision(2);
    _os << std::left;
    _os << std::setw(12) << _hd.m_date;
    _os << std::setw(5) << " / O=" << std::setw(6) << _hd.m_open <<
      " / H=" << std::setw(8) << _hd.m_high <<
      " / L=" << std::setw(8) << _hd.m_low <<
      " / C=" << std::setw(8) << _hd.m_close <<
      " / Volume=" << std::fixed << std::setw(12) << _hd.m_volume <<
      " / AdjClose=" << _hd.m_adjClose;
    return _os;
  }

}
