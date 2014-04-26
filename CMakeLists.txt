PROJECT(YAFIC)

Cmake_Minimum_Required(VERSION 2.8.9)

Set(YAFIC_MAJOR_VERSION    0)
Set(YAFIC_MINOR_VERSION    0)
Set(YAFIC_REVISION_VERSION a)

Set(YAFIC_VERSION ${YAFIC_MAJOR_VERSION}.${YAFIC_MINOR_VERSION})
If(YAFIC_REVISION_VERSION)
  Set(YAFIC_VERSION ${YAFIC_VERSION}.${YAFIC_REVISION_VERSION})
Endif(YAFIC_REVISION_VERSION)

Message(STATUS "YAFIC VERSION ${YAFIC_VERSION}")

Exec_Program(date ARGS "+%Y/%m/%d-%H:%M:%S" OUTPUT_VARIABLE BUILD_DATE )
Set(YAFIC_BUILD_VERSION ${BUILD_DATE})

Set( CMAKE_MODULE_PATH ${YAFIC_SOURCE_DIR}/cmake )

# Boost
Find_Package (Boost REQUIRED 
  thread filesystem program_options system date_time)

# Sqlite3
Find_Package(Sqlite3 REQUIRED)

Add_Subdirectory( src )

Option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

If(BUILD_DOCUMENTATION)
  Find_package (Doxygen)
  If (NOT DOXYGEN_FOUND)
    Message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  Endif() 
  Configure_File( 
    ${PROJECT_SOURCE_DIR}/doc/yafic.doxyfile.in
    ${PROJECT_BINARY_DIR}/doc/yafic.doxyfile @ONLY )
 
  Add_Custom_Target (doc
    ${DOXYGEN_EXECUTABLE} 
    ${PROJECT_BINARY_DIR}/doc/yafic.doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
ENDIF()
