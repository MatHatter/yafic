#ifndef __SQLITEMANAGER_HPP__
#define __SQLITEMANAGER_HPP__

#include <string>

#include <sqlite3.h>

namespace yafic {

  class SqliteManager {

  public:
    SqliteManager(const std::string& _fileName);

    virtual ~SqliteManager();

  protected:

  private:
    sqlite3 * m_db;
    std::string m_fileName;

  };

}

 #endif
