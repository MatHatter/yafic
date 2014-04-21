# YAFIC DATA LIBRARY
Set(YAFIC_DATA_SOURCES
  Stock.cpp
  Industry.cpp
  Sector.cpp
  SectorContainer.cpp
)
Set(YAFIC_DATA_LIB yaficdata)
Add_Library(${YAFIC_DATA_LIB} ${YAFIC_DATA_SOURCES})
