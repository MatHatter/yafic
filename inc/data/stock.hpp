#ifndef __STOCK_HPP__
#define __STOCK_HPP__

namespace yafic {

  class Stock {
  public:
    Stock(const std::string& _name,
	  const std::string& _symbol);

    std::string getName() const;

    std::string getSymbol() const;

  protected:

  private:

    std::string m_name;
    std::string m_symbol;
  };

}

#endif
