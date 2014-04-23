Find_Path(SQLITE3_INCLUDE_DIR sqlite3.h)

Find_Library(SQLITE3_LIBRARY NAMES sqlite3)

If (SQLITE3_INCLUDE_DIR AND SQLITE3_LIBRARY)
  Set(SQLITE3_FOUND TRUE)
Endif(SQLITE3_INCLUDE_DIR AND SQLITE3_LIBRARY)

If (SQLITE3_FOUND)
  Message(STATUS "Found Sqlite3 header file in ${SQLITE3_INCLUDE_DIR}")
  Message(STATUS "Found Sqlite3 library file in ${SQLITE3_LIBRARY}")
Else(SQLITE3_FOUND)
  If(SQLITE3_FIND_REQUIRED) 
    Message(FATAL_ERROR "Cound not find Sqlite3")
  Else(SQLITE3_FIND_REQUIRED)
    Message(STATUS "Optional package Sqlite3 was not found")
  Endif(SQLITE3_FIND_REQUIRED) 
Endif(SQLITE3_FOUND)
