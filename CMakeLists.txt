cmake_minimum_required (VERSION 2.8)
 
set (PROJECT_NAME "navi2pg") 
 
project (${PROJECT_NAME}) 

set(CMAKE_COLOR_MAKEFILE ON)

set (HEADERS 
        command_line_parser.h
        navi2pg.h
        logger.h)
 
set (SOURCES 
        command_line_parser.cpp
        navi2pg.cpp
        main.cpp)

find_package(GDAL REQUIRED)
if(GDAL_FOUND)
    include_directories(${GDAL_INCLUDE_DIR})
    include_directories(${GDAL_INCLUDE_DIR}/ogr)
    include_directories(${GDAL_INCLUDE_DIR}/ogr/ogrsf_frmts)
    include_directories(${GDAL_INCLUDE_DIR}/port)
    include_directories(${GDAL_INCLUDE_DIR}/gcore)
    include_directories(${GDAL_INCLUDE_DIR}/alg)
    include_directories(${GDAL_INCLUDE_DIR}/frmts/vrt)
    include_directories(${GDAL_INCLUDE_DIR}/build/port) #assume that out of source build was in build dir
endif(GDAL_FOUND)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARY})
