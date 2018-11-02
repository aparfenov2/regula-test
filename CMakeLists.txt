cmake_minimum_required (VERSION 2.8)
project (regula)

# ---------- dependencies ------------
find_package(OpenCV REQUIRED )
find_package(Boost REQUIRED )
find_package(GTest REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${GTEST_INCLUDE_DIR})
link_directories( ${Boost_LIBRARY_DIRS} )

message(STATUS "Hello ${CMAKE_INSTALL_LIBDIR}")

set( Boost_USE_STATIC_LIBS        OFF )
set( Boost_USE_MULTITHREADED      ON )
set( Boost_USE_STATIC_RUNTIME     OFF )
set( BOOST_ALL_DYN_LINK ON )

add_library(regulaDll SHARED src/dllmain.cpp)
target_link_libraries (regulaDll ${OpenCV_LIBS}) 

add_executable(conApp src/main.cpp)
target_link_libraries (conApp ${OpenCV_LIBS}) 
target_link_libraries (conApp ${Boost_LIBRARIES}) 
target_link_libraries (conApp regulaDll) 

add_executable(gtestApp src/main_ut.cpp)
target_link_libraries (gtestApp ${OpenCV_LIBS}) 
target_link_libraries (gtestApp ${Boost_LIBRARIES}) 
target_link_libraries (gtestApp ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY})
target_link_libraries (gtestApp regulaDll) 

install(TARGETS regulaDll conApp gtestApp
RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}"
ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}"
LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}")
