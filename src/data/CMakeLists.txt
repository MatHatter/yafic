# YAFIC DATA LIBRARY
Set(YAFIC_DATA_SOURCES
  Stock.cpp
  Industry.cpp
  Sector.cpp
  SectorContainer.cpp
  xml_parser.cpp
  SqliteManager.cpp
)
Set(YAFIC_DATA_LIB yaficdata)
Add_Library(${YAFIC_DATA_LIB} ${YAFIC_DATA_SOURCES})
# Target_Link_Libraries(${YAFIC_DATA_LIB} ${SQLITE3_LIBRARY})
