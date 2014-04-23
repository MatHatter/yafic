#include "data/SqliteManager.hpp"

#include <stdexcept>

namespace yafic {

  SqliteManager::SqliteManager(const std::string& _fileName) :
    m_fileName(_fileName) {
    int rc = sqlite3_open(m_fileName.c_str(), &m_db);
    if (rc) {
      std::string error = "Cannot initialize the database";
      throw std::runtime_error(error + sqlite3_errmsg(m_db));
    }
  }

  SqliteManager::~SqliteManager() {
    sqlite3_close(m_db);
  }

}
