Set(CMAKE_CXX_FLAGS "-std=c++11")
Include_Directories (${YAFIC_SOURCE_DIR}/inc)

Add_Subdirectory (data)
Add_Subdirectory (net)