# YAFIC NET LIBRARY
Set(YAFIC_NET_SOURCES
  yahoo_config.cpp
  http_helper.cpp
  yahoo_finance.cpp
)
Set(YAFIC_NET_LIB yaficnet)
Add_Library(${YAFIC_NET_LIB} ${YAFIC_NET_SOURCES})

Set(YQL_PROGRAMS yql_request get_industries do_request get_stocks get_histodata )

Foreach(program ${YQL_PROGRAMS})
  Add_Executable(${program} ${program}.cpp)
  Target_Link_Libraries(${program} 
    ${YAFIC_NET_LIB} 
    yaficdata
    ${Boost_LIBRARIES}
    )
  
Endforeach(program)
