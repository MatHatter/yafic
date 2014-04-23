# YAFIC NET LIBRARY
Set(YAFIC_NET_SOURCES
  yahoo_config.cpp
  http_helper.cpp
  yahoo_finance.cpp
)
Set(YAFIC_NET_LIB yaficnet)
Add_Library(${YAFIC_NET_LIB} ${YAFIC_NET_SOURCES})

# do_request program
Set(DO_REQUEST do_request)
Set(DO_REQUEST_SRC do_request.cpp)
Add_Executable(${DO_REQUEST} ${DO_REQUEST_SRC})
Target_Link_Libraries(${DO_REQUEST} ${Boost_LIBRARIES})

# yql_request program
Set(YQL_REQUEST yql_request)
Set(YQL_REQUEST_SRC yql_request.cpp)
Add_Executable(${YQL_REQUEST} ${YQL_REQUEST_SRC})
Target_Link_Libraries(${YQL_REQUEST} 
  ${Boost_LIBRARIES} 
  ${YAFIC_NET_LIB} 
  yaficdata)

# yql_request program
Set(YQL_GET_INDUSTRIES get_industries)
Set(YQL_GET_INDUSTRIES_SRC get_industries.cpp)
Add_Executable(${YQL_GET_INDUSTRIES} ${YQL_GET_INDUSTRIES_SRC})
Target_Link_Libraries(${YQL_GET_INDUSTRIES} 
  ${YAFIC_NET_LIB} 
  yaficdata
  ${Boost_LIBRARIES}

)

