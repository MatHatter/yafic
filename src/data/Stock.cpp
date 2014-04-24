/**
 * Copyright (c) 2014 ElAurens
 */

#include "data/Stock.hpp"

#include <string>

namespace yafic {
  Stock::Stock(const std::string& _name,
               const std::string& _symbol):
    m_name(_name),
    m_symbol(_symbol) {
  }

  std::string Stock::getName() const {
    return m_name;
  }

  std::string Stock::getSymbol() const {
    return m_symbol;
  }

}  // namespace yafic
