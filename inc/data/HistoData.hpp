#ifndef __HISTODATA_HPP__
#define __HISTODATA_HPP__

#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>


#include "data/yafic_types.hpp"

namespace yafic {

  class HistoData {

  public:
    HistoData(const boost::gregorian::date& _date);

    HistoData();

    virtual ~HistoData();

    void setOpen    (const decimal& _value);
    void setHigh    (const decimal& _value);
    void setLow     (const decimal& _value);
    void setClose   (const decimal& _value);
    void setVolume  (const decimal& _value);
    void setAdjClose(const decimal& _value);

    decimal getOpen    () const;
    decimal getHigh    () const;
    decimal getLow     () const;
    decimal getClose   () const;
    decimal getVolume  () const;
    decimal getAdjClose() const;

    friend std::ostream& operator <<(std::ostream& _os, const HistoData& _hd);
  protected:

  private:
    boost::gregorian::date m_date;
    decimal m_open, m_high, m_low, m_close, m_volume, m_adjClose;
  };

}

#endif
