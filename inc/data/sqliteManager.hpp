#ifndef __SQLITEMANAGER_HPP__
#define __SQLITEMANAGER_HPP__

namespace yafic {

  class SqliteManager {

  public:
    SqliteManager(const std::string& _fileName);

    virtual ~SqliteManager();

  protected:

  private:
    sqlite3 * db;
    std::string fileName;

  };

}

 #endif
